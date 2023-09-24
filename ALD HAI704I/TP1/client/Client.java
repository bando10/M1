package client;

//import commons.IAnimal;
import server.Animal;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {
    private Client() {}
    public static void main(String[] args){
        String port = (args.length < 1) ? null : args[0];
        try {
            Registry registry = LocateRegistry.getRegistry(port);
            Animal AnimalStub = (Animal) registry.lookup("Veterinaire");
            String reponse = AnimalStub.getNom();
            System.out.println(reponse);
        }
        catch (Exception e){
            System.err.println();
            e.printStackTrace();
        }
    }
}
