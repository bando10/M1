package Client;

public class Client {
    private int idClient;
    private String nom;
    private String prenom;
    private CB cb;

    public Client(int idClient, String nom, String prenom) {
        this.idClient = idClient;
        this.nom = nom;
        this.prenom = prenom;
        this.cb = null;
    }
    public Client(int idClient, String nom, String prenom, CB cb) {
        this.idClient = idClient;
        this.nom = nom;
        this.prenom = prenom;
        this.cb = cb;
    }

    @Override
    public String toString() {
        return "Client{" +
                "idClient=" + idClient +
                ", nom='" + nom + '\'' +
                ", prenom='" + prenom + '\'' +
                ", CB='" + cb.toString() + '\'' +
                '}';
    }

    public int getIdClient() {
        return idClient;
    }

    public void setIdClient(int idClient) {
        this.idClient = idClient;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public CB getCB() {
        return cb;
    }

    public void setCB(CB cb) {
        this.cb = cb;
    }
}
