package server;

import java.rmi.registry.LocateRegistry;

public class Server {
    //Constructor
    public Server() {

    }
    //Methodes

    public static void main(String[], args){
        try {
            server.AnimalImpl.AnimalImpl obj = new AnimalImpl.AnimalImpl();
            Registry registry = LocateRegistry.createRegistry(1099);

            if (registry == null){
                System.err.print("Port 1099 not found for registry");
            }
            else {
                registry.bind();
                System.err.print("Server ready;")
            }
        }
        
        
    }

    
    
}
