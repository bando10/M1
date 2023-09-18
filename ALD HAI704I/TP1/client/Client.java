package client;

import commons.Animal;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {
    private Client() {}
    public static void main(String[], args){
        String port = (args.length < 1) ? null : args[0];
        try {
            Registry registry = LocateRegistry.getRegistry(port);
            Animal AnimalStub = (Animal) registry.lookup();
            String reponse = AnimalStubtub.___();
            System.out.println();
        }
        catch (Exception e){
            System.err.println();
            e.printStackTrace();
        }
    }
}
