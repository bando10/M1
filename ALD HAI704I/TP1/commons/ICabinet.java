package commons;

import java.rmi.Remote;
import java.rmi.RemoteException;

import server.Animal;
import server.Espece;

public interface ICabinet extends Remote {
    public void addAnimal( String Nom, String Race, String NomMaitre, String NomEspece, String Duree) throws RemoteException;
    public String getNom() throws RemoteException;
    public IAnimal getAnimal(String nom) throws RemoteException;
    public String removeAnimal(String nom) throws RemoteException;
    public int getSize() throws RemoteException;
    public String[] stringAnimal() throws RemoteException;
    public boolean alerte() throws RemoteException;
}