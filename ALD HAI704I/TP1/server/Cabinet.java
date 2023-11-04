package server;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Arrays;

import commons.IAnimal;
import commons.ICabinet;


public class Cabinet extends UnicastRemoteObject implements ICabinet{
    private String name;
    private int nbPatients;
    private Animal[] patients;


    protected Cabinet(String nom) throws RemoteException{
        this.name = nom;
        this.nbPatients = 0;
        this.patients = new Animal[0];
    }
    @Override
    public IAnimal getAnimal(String nom) throws RemoteException{
        Animal search = null;
        for (Animal a : patients){
            if (a.getNom().equals(nom)){
                search = a;
            } else {
                System.out.print("Pas d'animal portant le nom: "+nom+" dans ce cabinet\n");
            }
        }
        return search;
    }

    @Override
    public void addAnimal(String Nom, String Race, String NomMaitre, String NomEspece, String Duree) throws RemoteException {
        int n = this.getSize()+1;
        Espece e = new Espece(NomEspece, Duree);
        Animal[] newPatients = new Animal[n];
        //System.arraycopy(this.patients, 0, newPatiens, 0, n);
        // Remplace la boucle dinit
        for(int i=0;i<n-1;i++) {
            newPatients[i]=this.patients[i];
        }
        this.patients=newPatients;
        this.patients[n-1]=new Animal(Nom, Race, NomMaitre, e);
        this.nbPatients += 1;
    }
    @Override
    public String removeAnimal(String nom) throws RemoteException{
        if (this.nbPatients == 0){
            return "Cabinet vide\n";
        }
        Animal[] newPatients = new Animal[this.nbPatients -1];
        int indice = 0;
        if (this.nbPatients == 1){
            this.patients = newPatients;
            this.nbPatients -= 1;
            return "Operation reussie, l'animal a ete enleve du cabinet qui est maintenant vide\n";
        }
        int i = 0;
        boolean trouve = false;
        while (i<this.nbPatients && !trouve){
            if (this.patients[i].getNom().equals(nom)){
                indice = i;
                trouve= true;
            }
            i++;
        }
        if (!trouve){
            return "Cet animal n'est pas dans le cabinet\n";
        }
        System.arraycopy(this.patients, 0, newPatients, 0, indice);

        if ( indice != this.nbPatients-1){
            if (this.nbPatients - (indice + 1) >= 0)
                System.arraycopy(this.patients, indice + 1, newPatients, indice + 1 - 1, this.nbPatients - (indice + 1));
        }
        this.patients=newPatients;
        this.nbPatients -= 1;
        return "Operation reussie, l'animal ne fait plus partie du cabinet\n";
    }


@Override
public int getSize() throws RemoteException{
    return this.nbPatients;
}

@Override
public String[] stringAnimal() throws RemoteException{
    String[] animals = new String[this.getSize()];
    int i = 0;
    for (Animal e : patients){
    animals[i] = e.StringAnimal();
    i += 1;
    }
    return animals;
}
@Override
    public String getNom() throws RemoteException{
        return this.name;
}
@Override
    public boolean alerte() throws RemoteException{
        int n = this.getSize();
        return ( n==100 || n == 500 || n == 1000);
}
}