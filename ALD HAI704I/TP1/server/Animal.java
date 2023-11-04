package server;

import commons.IAnimal;
import server.Espece;
import server.Dossier;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

//AnimalImpl

public class Animal extends UnicastRemoteObject implements IAnimal {
    private String Nom;
    private String NomProprio;
    private String Race;
    private Espece Espece;
    private Dossier Dossier;

    /*public Animal(String Nom, String NomProprio, String Race, String nomE, String dvmm) throws RemoteException{
        this.Nom = Nom;
        this.NomProprio = NomProprio;
        this.Race = Race;
        this.Espece = new Espece(nomE, dvmm);
        this.Dossier = new Dossier();
    }*/

    public Animal(String Nom, String NomProprio, String Race, Espece espece) throws RemoteException{
        this.Nom = Nom;
        this.NomProprio = NomProprio;
        this.Race = Race;
        this.Espece = espece;
        this.Dossier = new Dossier();
    }

    public Animal() throws RemoteException {
            super();
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
        return this.Espece.getEspece();
    }
    @Override
    public String StringAnimal() throws RemoteException{
        return "[Nom: "+getNom()+" || Nom du proprio: "+getNomProprio()+" || Race: "+getRace()+" || Espece:"+getEspece()+" || Dossier: "+ Dossier.getDossier() +"]\n";
    }
    @Override
    public String getDossier() throws RemoteException{
        return Dossier.getDossier();
    }
    @Override
    public void setDossier(String e, String d) throws RemoteException{
        Dossier.setDossier(e, d);
    }

    /*public void setDossier(String etat, String detail) {
        Dossier.etat = etat;
        Dossier.detail = detail;
    }*/
}
