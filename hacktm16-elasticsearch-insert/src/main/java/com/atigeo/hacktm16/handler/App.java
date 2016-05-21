package com.atigeo.hacktm16.handler;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
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
    private static String MONGO_COLLECTION = "drives";

    private static String MONGO_HOST = "localhost";
    private static int MONGO_PORT = 27017;

    private MongoClient mongoClient;
    private MongoDatabase mongoDatabase;

    public static void main(String[] args) throws InterruptedException {
        PropertyConfigurator.configure(App.class.getClassLoader().getResourceAsStream("log4j.xml"));

//        String ip = args[0];
//        String port = args[1];
        if(args.length != 1){
            LOGGER.warn(String.format("missing input: dump directory"));
            return;
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
            app.crawlDirectory(dumpDirectory);
            LOGGER.info("sleeping ... ");
            Thread.sleep(10 * 1000);
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

    private void crawlDirectory(String dumpDirectoryPath){

        File dumpDirectory = new File(dumpDirectoryPath);
        if(!dumpDirectory.isDirectory()){
            LOGGER.error("dump directory path is not a directory");
            return;
        }

        File[] listOfFiles = dumpDirectory.listFiles();
        Arrays.sort(listOfFiles);

        for(int i=0; i<listOfFiles.length - 1; i++){
            File file = listOfFiles[i];

            if(file.isDirectory())
                continue;

            String fileName = file.getName();
            if(!fileName.startsWith("drive_dump"))
                continue;

            LOGGER.info(String.format("dumping file: %s", file.getName()));

            String parentPath = file.getParent();
            String archivedFile = parentPath +File.separator+ "archived" +File.separator + file.getName();
            LOGGER.info(String.format("archived to: %s", archivedFile));

            processFile(file.getAbsolutePath(), archivedFile);

            file.delete();
        }
    }


    private void processFile(String fileName, String archivedFile){
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
                documents.add(dbObject);
                bufferedWriter.write(line);
            }

            collection.insertMany(documents);

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
        LOGGER.info(String.format("line read: %s", line));
        Document dbObject = null;
        try {
            ObjectMapper mapper = new ObjectMapper();
            ObjectNode jsonNode = mapper.readValue(line, ObjectNode.class);

            jsonNode = processJsonNode(jsonNode);
            LOGGER.info(String.format("processed : %s", jsonNode.toString()));

            Map<String, Object> result = mapper.convertValue(jsonNode, Map.class);

            dbObject = new Document(result);

        } catch (IOException e) {
            LOGGER.error("json exception");
        } catch (Exception e) {
            LOGGER.error("json exception");
        }
        return dbObject;
    }

    private ObjectNode processJsonNode(ObjectNode jsonNode) throws Exception{

        //process speed
        JsonNode speedValue = jsonNode.get("speed");
        double speedDoubleMs = speedValue.asDouble();
        double speedDoubleKmh = 3.6 * speedDoubleMs;

        jsonNode = jsonNode.put("speedkmh", speedDoubleKmh);
        jsonNode = jsonNode.put("speedms",speedDoubleMs);

        //unix time
        JsonNode driveTimeValue = jsonNode.get("drivetime");
        String driveTime = driveTimeValue.asText();
        String year = driveTime.substring(0, 4);
        String month = driveTime.substring(4, 6);
        String day = driveTime.substring(6, 8);
        String hour = driveTime.substring(8, 10);
        String minute = driveTime.substring(10, 12);
        String second = driveTime.substring(12, 14);
        String ms = driveTime.substring(14, 15);

        int y = Integer.valueOf(year);
        int m = Integer.valueOf(month);
        int d = Integer.valueOf(day);
        int hh = Integer.valueOf(hour);
        int mm = Integer.valueOf(minute);
        int ss = Integer.valueOf(second);
        int mss = Integer.valueOf(ms);

        Calendar calendar = new GregorianCalendar(y, m, d, hh, mm, ss);
        calendar.set(Calendar.MILLISECOND, mss);
        long utc = calendar.getTimeInMillis();

        jsonNode = jsonNode.put("unixtime", utc);

        return jsonNode;
    }



    private MongoClient establishESConnection() throws UnknownHostException {
        MongoClient mongo = new MongoClient(MONGO_HOST, MONGO_PORT);
        return mongo;
    }

}
