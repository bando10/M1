package server;
//import server.Animal;
import commons.*;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.AlreadyBoundException;

import static java.lang.System.*;

public class Server {
    //Constructor
    public Server() {

    }
    //Methodes
    /*
    public void startSecurityManager(){
        SecurityManager sm = new SecurityManager();
        System.setProperty("java.security.policy", "security.security.policy");
        System.setSecurityManager(sm);

    }
     */
    public static void main(String[] args){
        try {
            /*
            Dossier dossierChienBob = new Dossier();
            Espece chien = new Espece("Chien", "130");
            Animal obj = new Animal("chiendebob", "Bob", "Doberman", chien, dossierChienBob);*/
            Cabinet cab = new Cabinet("Veterinaire");
            Registry registry = LocateRegistry.createRegistry(1099);

            if (registry == null){
                err.print("Port 1099 not found for registry");
            }
            else {
                registry.bind("Veterinaire", cab);
                System.out.print("Server ready;");
            }
        }
        catch (RemoteException e) {
            e.printStackTrace();
        } catch (AlreadyBoundException e) {
            e.printStackTrace();
        }
        
        
    }

    
    
}
