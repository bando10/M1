package client;

import commons.IAnimal;
import commons.ICabinet;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

import static jdk.internal.net.http.common.Utils.close;

public class Client {
    private Client() {}
    public static void main(String[] args){
        String port = (args.length < 1) ? null : args[0];
        try {
            Registry registry = LocateRegistry.getRegistry(port);
            if (registry == null){
                System.err.print("Port not found for registry");
                close();
            }
            else {
                System.out.print("Client ready;\n");
            }
            //assert registry != null;
            //IAnimal AnimalStub = (IAnimal) registry.lookup("Animal");
            ICabinet CabinetStub = (ICabinet) registry.lookup("Veterinaire");
            /*String reponse = AnimalStub.getDossier();
            System.out.println(reponse);*/
            System.out.println("Bonjour "+CabinetStub.getNom()+" voici les options:\n" + "1 : Voir les patients\n" + "2 : Recherche de patient par nom\n" + "3 : Creation patient \n" + "4 : Suppression patient\n" + "5 : Modification dossier suivi d'un patient\n('q' pour quitter)\n");
            String choix = null;
            Scanner scan = new Scanner(System.in);

            do {
                choix = scan.nextLine();
                switch (choix) {
                    case "1":
                        System.out.println("[Voir les patients du cabinet]\n");

                        int n = CabinetStub.getSize();
                        if (n == 0) {
                            System.out.println("il n'y a pas de patient dans le cabinet");
                        } else {
                            String reponse[] = CabinetStub.stringAnimal();
                            for (int i = 0; i < n; i++) {
                                System.out.println(reponse[i]);

                                }
                        }
                        break;
                    case "2":
                        System.out.println("[Recherche de patient par nom]\n");
                        System.out.println("Nom du patient? ");
                        String nomP = scan.nextLine();
                        IAnimal an = CabinetStub.getAnimal(nomP);
                        if(an == null) {
                            System.out.println("Ce patient n'existe pas");
                        }else {
                            System.out.println(an.StringAnimal());
                        }
                        break;
                    case "3":
                        System.out.println("[Creation de patient]\n");
                        System.out.println("Espece ? \n");
                        String espece = scan.nextLine();
                        System.out.println("Race? \n");
                        String race = scan.nextLine();
                        System.out.println("Duree de vie de l'espece(en mois)? \n");
                        String dureeV = scan.nextLine();
                        System.out.println("Nom?\n ");
                        String nom = scan.nextLine();
                        System.out.println("Nom du Maitre? \n");
                        String nMaitre = scan.nextLine();
                        CabinetStub.addAnimal(nom, race, nMaitre, espece, dureeV);
                        System.out.println("Patient bien ajouté au cabinet !");
                        if(CabinetStub.alerte()) {
                            System.out.println("Seuil de "+ CabinetStub.getSize() + " patients dans le cabinet atteint.\n ");
                        }
                        break;
                    case "4":
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
                        break;
                }
            } while (!choix.equals("q"));
            scan.close();}
        /*catch (Exception e){
            System.err.println();
            e.printStackTrace();
        }*/
        catch (RemoteException | NotBoundException e) {
            e.printStackTrace();
        }
    }
}
