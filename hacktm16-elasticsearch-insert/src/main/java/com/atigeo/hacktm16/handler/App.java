package com.atigeo.hacktm16.handler;

import org.apache.log4j.PropertyConfigurator;
import org.elasticsearch.client.Client;
import org.elasticsearch.client.transport.TransportClient;
import org.elasticsearch.common.transport.InetSocketTransportAddress;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Arrays;

/**
 * Created by cipri on 5/21/16.
 */
public class App {

    private static final Logger LOGGER = LoggerFactory.getLogger(App.class);

    public static void main(String[] args){
        PropertyConfigurator.configure(App.class.getClassLoader().getResourceAsStream("log4j.xml"));

//        String ip = args[0];
//        String port = args[1];
        if(args.length != 1){
            LOGGER.warn(String.format("missing input: dump directory"));
            return;
        }
        String dumpDirectory = args[0];

        LOGGER.info(String.format("Started with dir: %s", dumpDirectory));
        crawlDirectory(dumpDirectory);
    }


    private static void crawlDirectory(String dumpDirectoryPath){

        File dumpDirectory = new File(dumpDirectoryPath);
        if(!dumpDirectory.isDirectory()){
            LOGGER.error("dump directory path is not a directory");
            return;
        }

        File[] listOfFiles = dumpDirectory.listFiles();
        Arrays.sort(listOfFiles);

        for(File file: listOfFiles){
            LOGGER.info(String.format("dumping file: %s", file.getAbsolutePath()));

            archiveProcessedFile(file);
        }
    }

    private static void archiveProcessedFile(File oldFile){
        try{
            String parentPath = oldFile.getParent();
            LOGGER.info(String.format("Moving file: %s from dir: %s", oldFile.getName(), parentPath));

            if(oldFile.renameTo(new File(parentPath +File.pathSeparator+ "old" +File.pathSeparator + oldFile.getName()))){
                LOGGER.info("File is moved successful!");
            }else{
                LOGGER.warn("File is failed to move!");
            }

        }catch(Exception e){
            LOGGER.error("file archive error", e);
        }
    }

    private static void readFile(String fileName){

        try {
            FileReader fileReader = new FileReader(fileName);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line ;
            while((line = bufferedReader.readLine()) != null) {
                processLine(line);
            }

            // Always close files.
            bufferedReader.close();
        }
        catch(FileNotFoundException ex) {
            LOGGER.error(String.format("Unable to open file %s", fileName), ex);
        }
        catch(IOException ex) {
            LOGGER.error(String.format("error reading file %s", fileName), ex);
        }

    }

    private static void processLine(String line){
        LOGGER.info(String.format("line read: %s", line));


    }


    private static Client establishESConnection() throws UnknownHostException {
        Client client = null;
        try {
            client = TransportClient.builder().build()
                    .addTransportAddress(new InetSocketTransportAddress(InetAddress.getByName("hack-es"), 9300));
            LOGGER.info("Connection to ElasticSearch established !");
        }
        catch (Exception e){

            LOGGER.error("ES connection error", e);
        }

        return client;
    }

}
