package Reservation;

import Client.Client;
import Hotel.Chambre;



import java.time.LocalDate;

public class Reservation {
    private Client client;
    private Chambre chambre;
    private LocalDate debut;
    private LocalDate fin;
    private int nbPersonnes;



    public Reservation(Client client, Chambre chambre, LocalDate debut, LocalDate fin, int nbPersonnes) {
        this.client = client;
        this.chambre = chambre;
        this.debut = debut;
        this.fin = fin;
        this.nbPersonnes = nbPersonnes;
    }

    @Override
    public String toString() {
        return "Reservation{" +
                "client=" + client +
                ", chambre=" + chambre +
                ", debut=" + debut +
                ", fin=" + fin +
                ", nbPersonnes=" + nbPersonnes +
                '}';
    }
    public LocalDate getDebut() {
        return debut;
    }

    public void setDebut(LocalDate debut) {
        this.debut = debut;
    }

    public LocalDate getFin() {
        return fin;
    }

    public void setFin(LocalDate fin) {
        this.fin = fin;
    }

    public int getNbPersonnes() {
        return nbPersonnes;
    }

    public void setNbPersonnes(int nbPersonnes) {
        this.nbPersonnes = nbPersonnes;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public Chambre getChambre() {
        return chambre;
    }

    public void setChambre(Chambre chambre) {
        this.chambre = chambre;
    }
}
