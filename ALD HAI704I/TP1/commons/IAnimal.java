package commons;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IAnimal extends Remote {
    String getNom() throws RemoteException;
    String getNomProprio() throws RemoteException;
    String getRace() throws RemoteException;
    String getEspece() throws RemoteException;
    String StringAnimal() throws RemoteException;
} 

