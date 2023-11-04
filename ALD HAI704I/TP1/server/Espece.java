package server;

import java.rmi.RemoteException;
import java.io.Serializable;

public class Espece extends Animal implements Serializable {
    private String nomEspece;
    private String dureeVieMoyMois;

    public Espece(String nomE, String dvmm) throws RemoteException{
        this.nomEspece = nomE;
        this.dureeVieMoyMois = dvmm;
    }

    public Espece(String Nom, String NomProprio, String Race, server.Espece espece) throws RemoteException {
        super(Nom, NomProprio, Race, espece);
    }

    public String getNom() {
        return nomEspece;
    }

    public String getDureeVieMoyMois() {
        return dureeVieMoyMois;
    }


    public String getEspece() {
        return "[(Espece): " +
                "nomEspece= " + this.nomEspece + " || "+
                "dureeVieMoyMois= " + this.dureeVieMoyMois +
                "]\n";
    }
}
