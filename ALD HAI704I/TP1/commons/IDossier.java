package commons;
import server.Dossier;

import java.rmi.RemoteException;
import java.rmi.Remote;

public interface IDossier extends Remote {

    String getEtat() throws RemoteException;
    String getDetail() throws RemoteException;
    void setEtat(String Etat) throws RemoteException;
    void setDetail(String Detail) throws RemoteException;
    String getDossier() throws RemoteException;

    void setDossier(String etat, String det) throws RemoteException;
}
