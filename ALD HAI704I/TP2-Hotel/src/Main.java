import Hotel.Chambre;
import Hotel.Hotel;
import Client.*;
import Reservation.Reservation;

import java.time.LocalDate;
import java.util.Scanner;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {

        System.out.println("Bonjour voici les options:\n" + "1 : Creer hotel\n" + "2 : addChambre a hotel\n" + "3 : Creation client \n" + "4 : Voir chambres\n" + "5 : Client\n" + "6 : Suppression\n('q' pour quitter)\n");
        String choix = null;
        Scanner scan = new Scanner(System.in);
        System.out.println("[Creation hotel]\n");
        System.out.println("Nom ? \n");
        String nom = scan.nextLine();
        System.out.println("Pays? \n");
        String pays = scan.nextLine();
        System.out.println("Ville? \n");
        String ville = scan.nextLine();
        System.out.println("Adresse?\n ");
        String adresse = scan.nextLine();
        Hotel hotel = new Hotel(nom, pays, ville, adresse);
        System.out.println("Creation hotel reussie:\n"+hotel.toString()+"\n");
        do {
            choix = scan.nextLine();
            switch (choix) {
                case "1":

                    break;
                case "2":
                    System.out.println("[addChambre a hotel]\n");
                    //System.out.println("Nom de l'hotel? ");
                    System.out.println("Nb de lits?\n");
                    int nbl = Integer.parseInt(scan.nextLine());
                    System.out.println("Prix?\n");
                    double prix = Double.parseDouble(scan.nextLine());
                    hotel.addChambre(nbl, prix);
                    System.out.println(hotel.toString()+"\n");

                    break;
                case "3":
                    System.out.println("[Creation client]\n");
                    System.out.println("Nom ? \n");
                    String nomCl = scan.nextLine();
                    System.out.println("Prenom? \n");
                    String prenom = scan.nextLine();
                    System.out.println("idClient? \n");
                    int idc = Integer.parseInt(scan.nextLine());
                    Client client = new Client(idc, nomCl, prenom);
                    System.out.println("CB?(y/n)\n ");
                    String s = scan.nextLine();
                    //char cbbool = s.charAt(0);
                    if (s.equals("y")){
                        System.out.println("Numero carte? \n");
                        int numCb = Integer.parseInt(scan.nextLine());
                        System.out.println("Date emission ? \n");
                        LocalDate em = LocalDate.parse(scan.nextLine());
                        System.out.println("Date expiration? \n");
                        LocalDate exp = LocalDate.parse(scan.nextLine());
                        CB cb = new CB(numCb, prenom + " " + nomCl, em, exp);
                        client.setCB(cb);}
                    System.out.println(client.toString() + " \n");
                    break;
                /*case "4":
                    System.out.println("[Suppression patient] \n");
                    System.out.println("Nom? \n");
                    String nomSuppr = scan.nextLine();
                    String supprP = CabinetStub.removeAnimal(nomSuppr);
                    System.out.println(supprP);
                    if(CabinetStub.alerte()) {
                        System.out.println("Seuil de "+ CabinetStub.getSize() + " patients dans le cabinet atteint.\n ");
                    }
                    break;
                case "5":
                    System.out.println("[Modification dossier suivi patient]\n ");
                    System.out.println("Nom? \n");
                    String nomD = scan.nextLine();
                    IAnimal ani = CabinetStub.getAnimal(nomD);
                    if(ani == null) {
                        System.out.println("Ce patient n'existe pas.\n");
                        break;
                    }else {
                        System.out.println("Etat du patient ?");
                        String etat = scan.nextLine();
                        System.out.println("Details ?");
                        String detail = scan.nextLine();
                        ani.setDossier(etat, detail);
                    }
                    break;*/
            }
        } while (!choix.equals("q"));
        scan.close();}
    }
