
public class UtilisationDictionnaire {
	public static void main(String[] args) {
	    IDictionary Order = new OrderedDictionary();
	    System.out.println("Tableau Vide ? : " + Order.isEmpty() + " | Taille : " + Order.size());
	    Order.put("comprendre", "Saisir par l'esprit, l'intelligence ou le raisonnement quelque chose");
	    System.out.println("Tableau Vide ? : " + Order.isEmpty() + "  | Taille : " + Order.size());
		System.out.println(Order.containsKey("comprendre")? "Le dico contient \"comprendre\"" : "Le dico ne contient pas \"comprendre\"");
		System.out.println("Recherche de la definition comprendre ? : " + Order.get("comprendre"));

		IDictionary Fast = new FastDictionary();
		System.out.println("Tableau Vide ? : " + Fast.isEmpty() + " | Taille : " + Fast.size());
		//((FastDictionary)Fast).grow();
		Fast.
		System.out.println("Tableau Vide ? : " + Fast.isEmpty() + " | Taille : " + Fast.size());
		Fast.put("Fast", "Aller vite");
		System.out.println("Tableau Vide ? : " + Fast.isEmpty() + "  | Taille : " + Fast.size());
		System.out.println(Order.containsKey("Fast")? "Le dico contient \"Fast\"" : "Le dico ne contient pas \"Fast\"");
		System.out.println("Recherche de la definition Fast: " + Fast.get("Fast"));
		//System.out.println("Indexof \"Fast\": " + Fast.indexOf("Fast"));
		//Fast.grow();
		//System.out.println("NewIndexof \"Fast\": " + Fast.newIndexOf("Fast"));

	  }
}
