package commons;
  import java.rmi.Remote;
  import java.rmi.registry.Registry;
  import java.rmi.registry.LocateRegistry;
  import java.rmi.RemoteException;
  import java.rmi.server.UnicastRemoteObject;

public interface Animal extends Remote {
    String nom();
    String nomProprio();
    String race();
    String espece();
} 

