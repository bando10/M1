package server;

import commons.IDossier;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;




public class Dossier extends UnicastRemoteObject implements IDossier {
    private String Etat;
    private String Detail;

    //Constructors
    public Dossier() throws RemoteException{
        this.Etat = "inconnu";
        this.Detail = "inconnu";
    }

    public Dossier(String Etat, String Detail) throws RemoteException{
        this.Etat = Etat;
        this.Detail = Detail;
    }

    @Override
    public String getEtat() throws RemoteException{
        return this.Etat;
    }
    @Override
    public String getDetail() throws RemoteException{
        return this.Detail;
    }
    @Override
    public  void setEtat(String Etat) throws RemoteException{
        this.Etat = Etat;
    }
    @Override
    public void setDetail(String Detail) throws RemoteException{
        this.Detail = Detail;
    }
    @Override
    public String getDossier() throws RemoteException{
        return "[Etat: "+getEtat()+" || Detail: "+getDetail()+"]\n";
    }
    @Override
    public void setDossier(String etat, String det) throws RemoteException{
        setEtat(etat);
        setDetail(det);
    }

}
