package com.atigeo.hacktm16.handler;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.ObjectNode;
import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.apache.log4j.PropertyConfigurator;
import org.bson.Document;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.net.UnknownHostException;
import java.util.*;

/**
 * Created by cipri on 5/21/16.
 */
public class App {

    private static final Logger LOGGER = LoggerFactory.getLogger(App.class);

    private static String MONGO_DATABASE = "hacktm";
//    private static String MONGO_COLLECTION = "drives";
//    private static String MONGO_COLLECTION = "demo";
//    private static String MONGO_COLLECTION = "mock";
    private static String MONGO_COLLECTION = "realtime";

    private static long FILE_SLEEP = 1 * 1000;
    private static long BATCH_SLEEP = 1 * 1000;
    private static long DIR_SLEEP = 5 * 1000;

    private static int BATCH_SIZE = 1500;

    private static String MONGO_HOST = "hack-mongo";
    private static int MONGO_PORT = 27017;

    private MongoClient mongoClient;
    private MongoDatabase mongoDatabase;

    private static long recordingId = System.currentTimeMillis();

    public static void main(String[] args) throws InterruptedException {
        PropertyConfigurator.configure(App.class.getClassLoader().getResourceAsStream("log4j.xml"));

//        String ip = args[0];
//        String port = args[1];
        if(args.length < 1){
            LOGGER.warn(String.format("missing input: dump directory"));
            return;
        }

        boolean streaming = false;
        if(args.length == 2){
            streaming = true;
        }

        if(!streaming){
            BATCH_SLEEP = 0;
            FILE_SLEEP = 0;
        }



        String dumpDirectory = args[0];

        App app = new App();

        try {
            app.connectMongoDb();
            app.checkCollection();
        } catch (UnknownHostException e) {
           LOGGER.error("mongo connection", e);
            return;
        }

        LOGGER.info(String.format("Started with dir: %s", dumpDirectory));
        while(true) {
            LOGGER.info("crawling ... ");
            app.crawlDirectory(dumpDirectory, streaming);
            LOGGER.info("sleeping ... ");
            Thread.sleep(DIR_SLEEP);
        }
    }

    private  void connectMongoDb() throws UnknownHostException {
        mongoClient = establishESConnection();

        mongoDatabase = mongoClient.getDatabase(MONGO_DATABASE);
    }



    private void checkCollection(){
        MongoCollection<Document> collection = mongoDatabase.getCollection(MONGO_COLLECTION);
        if(collection == null){
            mongoDatabase.createCollection(MONGO_COLLECTION);
        }
    }

    private void crawlDirectory(String dumpDirectoryPath, boolean streaming) throws InterruptedException {

        File dumpDirectory = new File(dumpDirectoryPath);
        if(!dumpDirectory.isDirectory()){
            LOGGER.error("dump directory path is not a directory");
            return;
        }

        int lastDirectory = 0;
        if(streaming){
            lastDirectory = 1;
        }

        File[] listOfFiles = dumpDirectory.listFiles();
        Arrays.sort(listOfFiles);


        for(int i=0; i<listOfFiles.length - lastDirectory; i++){
            File file = listOfFiles[i];

            if(file.isDirectory())
                continue;

            String fileName = file.getName();
            if(!fileName.startsWith("drive_dump") && !fileName.startsWith("MOCK_DATA"))
                continue;

            LOGGER.info(String.format("dumping file: %s", file.getName()));

            String parentPath = file.getParent();
            String archivedFile = parentPath +File.separator+ "archived" +File.separator + file.getName();
            LOGGER.info(String.format("archived to: %s", archivedFile));

            if(FILE_SLEEP > 1000)
                Thread.sleep(FILE_SLEEP);

            processFile(file.getAbsolutePath(), archivedFile);

            file.delete();
        }
    }


    private void processFile(String fileName, String archivedFile) throws InterruptedException {
        LOGGER.info(String.format("PROCESSING FILE %s", fileName));

        MongoCollection<Document> collection = mongoDatabase.getCollection(MONGO_COLLECTION);

        try {
            FileReader fileReader = new FileReader(fileName);
            FileWriter fileWriter = new FileWriter(archivedFile);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

            String line ;
            List<Document> documents = new ArrayList<>();
            while((line = bufferedReader.readLine()) != null) {
                Document dbObject = processLine(line);
                if(dbObject == null)
                    continue;

                documents.add(dbObject);
                bufferedWriter.write(line);

                if(documents.size() >= BATCH_SIZE){
                    collection.insertMany(documents);
                    documents.clear();
                    if(BATCH_SLEEP > 1000)
                        Thread.sleep(BATCH_SLEEP);
                }
            }

            if(documents.size() > 2)
                collection.insertMany(documents);

            LOGGER.info(String.format("documents written: %d", documents.size()));

            bufferedReader.close();
            bufferedWriter.close();
        }
        catch(FileNotFoundException ex) {
            LOGGER.error(String.format("Unable to open file %s", fileName), ex);
        }
        catch(IOException ex) {
            LOGGER.error(String.format("error reading file %s", fileName), ex);
        }

    }

    private Document processLine(String line){
//        LOGGER.info(String.format("line read: %s", line));
        Document dbObject = null;
        try {
            ObjectMapper mapper = new ObjectMapper();
            ObjectNode jsonNode = mapper.readValue(line, ObjectNode.class);

            jsonNode = processJsonNode(jsonNode);
            if(jsonNode == null)
                return null;
//            LOGGER.info(String.format("processed : %s", jsonNode.toString()));

            Map<String, Object> result = mapper.convertValue(jsonNode, Map.class);

            dbObject = new Document(result);

        } catch (IOException e) {
            LOGGER.error("json exception", e);
            LOGGER.info(String.format("line read: %s", line));
        } catch (Exception e) {
            LOGGER.error("json exception", e);
            LOGGER.info(String.format("line read: %s", line));
        }
        return dbObject;
    }

    private ObjectNode processJsonNode(ObjectNode jsonNode) throws Exception{

        ObjectMapper mapper = new ObjectMapper();

        //process speed
        JsonNode speedValue = jsonNode.get("speed");
        if(speedValue != null) {
            double speedDoubleMs = speedValue.asDouble();
            double speedDoubleKmh = 3.6 * speedDoubleMs;
            jsonNode = jsonNode.put("speedkmh", speedDoubleKmh);
            jsonNode = jsonNode.put("speedms",speedDoubleMs);

        }

        if(jsonNode.has("longitude")) {
            //                                              longitude & latitude
            //   "geo" : { "type" : "Point", "coordinates" : [ -121.88355687, 37.44609999 ] }
            ArrayNode jNode = mapper.createArrayNode();
            double longitude = jsonNode.get("longitude").asDouble();
            double latitude = jsonNode.get("latitude").asDouble();
            if (longitude > 1000 || longitude < -1000)
                return null;
            if (latitude > 1000 || latitude < -1000)
                return null;
            jNode = jNode.add(jsonNode.get("longitude").asDouble());
            jNode = jNode.add(jsonNode.get("latitude").asDouble());
            Map<String, JsonNode> geoMap = new HashMap<>();
            geoMap.put("coordinates", jNode);
            ObjectNode geo = mapper.createObjectNode();
            geo = geo.put("type", "Point");
            JsonNode geoJson = geo.setAll(geoMap);
            Map<String, JsonNode> geoMapComplete = new HashMap<>();
            geoMapComplete.put("geo", geoJson);
            jsonNode = (ObjectNode) jsonNode.set("geo", geoJson);
        }

        if(jsonNode.has("drivetime")) {

            //unix time
            JsonNode driveTimeValue = jsonNode.get("drivetime");
            String driveTime = driveTimeValue.asText();
            if(driveTime.length() != 15){
                Calendar cal = new GregorianCalendar();
                cal.setTimeInMillis(System.currentTimeMillis());
                driveTime = "" + cal.get(Calendar.YEAR)
                        + (cal.get(Calendar.MONTH) > 10 ? cal.get(Calendar.MONTH) : ("0" + cal.get(Calendar.MONTH) ))
                        + (cal.get(Calendar.DAY_OF_MONTH) > 10 ? cal.get(Calendar.DAY_OF_MONTH) : ("0" + cal.get(Calendar.DAY_OF_MONTH) ))
                        + (cal.get(Calendar.HOUR_OF_DAY) > 10 ? cal.get(Calendar.HOUR_OF_DAY) : ("0" + cal.get(Calendar.HOUR_OF_DAY) ))
                        + (cal.get(Calendar.MINUTE) > 10 ? cal.get(Calendar.MINUTE) : ("0" + cal.get(Calendar.MINUTE) ))
                        + (cal.get(Calendar.SECOND) > 10 ? cal.get(Calendar.SECOND) : ("0" + cal.get(Calendar.SECOND) ))
                        + cal.get(Calendar.MILLISECOND);
            }

            String year = driveTime.substring(0, 4);
            String month = driveTime.substring(4, 6);
            String day = driveTime.substring(6, 8);
            String hour = driveTime.substring(8, 10);
            String minute = driveTime.substring(10, 12);
            String second = driveTime.substring(12, 14);
            String ms = driveTime.substring(14, 15);

            jsonNode = jsonNode.put("ingestiontime", System.currentTimeMillis());

            int y = Integer.valueOf(year);
            int m = Integer.valueOf(month);
            int d = Integer.valueOf(day);
            int hh = Integer.valueOf(hour);
            int mm = Integer.valueOf(minute);
            int ss = Integer.valueOf(second);
            int mss = Integer.valueOf(ms);

            jsonNode = jsonNode.put("year", y);
            jsonNode = jsonNode.put("month", m);
            jsonNode = jsonNode.put("day", d);
            jsonNode = jsonNode.put("hour", hh);
            jsonNode = jsonNode.put("minute", mm);
            jsonNode = jsonNode.put("second", ss);
            jsonNode = jsonNode.put("millisecond", mss);

            Calendar calendar = new GregorianCalendar(y, m, d, hh, mm, ss);
            calendar.set(Calendar.MILLISECOND, mss);
            long utc = calendar.getTimeInMillis();

            jsonNode = jsonNode.put("unixtime", utc);
        }

        jsonNode = jsonNode.put("ingestiontime", System.currentTimeMillis());

        if(!jsonNode.has("recordingid")){
            jsonNode = jsonNode.put("recordingid", recordingId);
        }

        return jsonNode;
    }



    private MongoClient establishESConnection() throws UnknownHostException {
        MongoClient mongo = new MongoClient(MONGO_HOST, MONGO_PORT);
        return mongo;
    }

}
