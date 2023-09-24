package server;
import server.Animal;


import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.AlreadyBoundException;
public class Server {
    //Constructor
    public Server() {

    }
    //Methodes

    public static void main(String[] args){
        try {
            Animal obj = new Animal("chiendebob", "Bob", "Doberman", "chien");
            Registry registry = LocateRegistry.createRegistry(1099);

            if (registry == null){
                System.err.print("Port 1099 not found for registry");
            }
            else {
                registry.bind("Animal", obj);
                System.err.print("Server ready;");
            }
        }
        catch (RemoteException e) {
            e.printStackTrace();
        } catch (AlreadyBoundException e) {
            e.printStackTrace();
        }
        
        
    }

    
    
}
