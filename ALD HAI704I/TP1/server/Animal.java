package server;

import commons.IAnimal;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Animal extends UnicastRemoteObject implements IAnimal {
    private String Nom;
    private String NomProprio;
    private String Race;
    private String Espece;

    Animal(String Nom, String NomProprio, String Race, String Espece) throws RemoteException{
        this.Nom = Nom;
        this.NomProprio = NomProprio;
        this.Race = Race;
        this.Espece = Espece;
    }

    @Override
    public String getNom() throws RemoteException{
        return this.Nom;
    }
    @Override
    public String getNomProprio() throws RemoteException{
        return this.NomProprio;
    }
    @Override
    public String getRace() throws RemoteException{
        return this.Race;
    }
    @Override
    public String getEspece() throws RemoteException{
        return this.Espece;
    }
    @Override
    public String StringAnimal() throws RemoteException{
        return "[Nom: "+getNom()+" || Nom du proprio: "+getNomProprio()+" || Race: "+getRace()+" || Espece:"+getEspece()+"]\n";
    }
}
