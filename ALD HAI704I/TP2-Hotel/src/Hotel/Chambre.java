package  Hotel;

public class Chambre {
    private int cap;
    private double prix;
    private boolean libre;

    public Chambre(int cap, double prix) {
        this.cap = cap;
        this.prix = prix;
        this.libre = true;
    }

    public int getCap() {
        return cap;
    }

    public void setCap(int cap) {
        this.cap = cap;
    }

    public boolean isLibre() {
        return libre;
    }

    public void setLibre(boolean libre) {
        this.libre = libre;
    }

    public double getPrix() {
        return prix;
    }

    public void setPrix(double prix) {
        this.prix = prix;
    }
    @Override
    public String toString() {
        return "Chambre{" +
                "cap=" + cap +
                ", prix=" + prix +
                ", libre=" + (libre? "oui":"non") +
                '}';
    }
}

