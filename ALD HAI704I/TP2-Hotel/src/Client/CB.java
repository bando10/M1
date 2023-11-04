package Client;

import java.time.LocalDate;

public class CB {
    private int numCarte;
    private String titulaire;
    private LocalDate emission;
    private LocalDate expiration;

    public CB(int numCarte, String titulaire, LocalDate emission, LocalDate expiration) {
        this.numCarte = numCarte;
        this.titulaire = titulaire;
        this.emission = emission;
        this.expiration = expiration;
    }

    @Override
    public String toString() {
        return "CB{" +
                "numCarte=" + numCarte +
                ", titulaire='" + titulaire + '\'' +
                ", emission=" + emission +
                ", expiration=" + expiration +
                '}';
    }
}
