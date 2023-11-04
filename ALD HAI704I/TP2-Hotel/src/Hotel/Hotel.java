package Hotel;

import java.util.ArrayList;
import Reservation.Reservation;

public class Hotel {
    private String nom;
    private String pays;
    private String ville;
    private String adresse;
    ArrayList<Chambre> chambres;
    ArrayList<Reservation> reservations;

    public Hotel(String nom, String pays, String ville, String adresse) {
        this.nom = nom;
        this.pays = pays;
        this.ville = ville;
        this.adresse = adresse;
        this.chambres = new ArrayList<Chambre>();
        this.reservations = new ArrayList<Reservation>();
    }

    public Hotel(){
        this.nom = "";
        this.pays = "";
        this.ville = "";
        this.adresse = "";
        this.chambres = new ArrayList<Chambre>();
        this.reservations = new ArrayList<Reservation>();
    }

    public void addChambre(int nbLits, double prix){
        Chambre c = new Chambre(nbLits, prix);
        chambres.add(c);
    }
    public void deleteChambre(Chambre c){
        chambres.remove(c);
    }
    public void reserver(){

    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPays() {
        return pays;
    }

    public void setPays(String pays) {
        this.pays = pays;
    }

    public String getVille() {
        return ville;
    }

    public void setVille(String ville) {
        this.ville = ville;
    }

    public String getAdresse() {
        return adresse;
    }

    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }


    @Override
    public String toString() {
        return "Hotel{" +
                "nom='" + nom + '\'' +
                ", pays='" + pays + '\'' +
                ", ville='" + ville + '\'' +
                ", adresse='" + adresse + '\'' +
                '}';
    }




}

