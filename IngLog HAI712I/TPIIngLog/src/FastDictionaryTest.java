import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class FastDictionaryTest {
	
	static IDictionary Fast = new FastDictionary();

	@BeforeAll
	static void set() {
	    Fast.put("comprendre", "Saisir par l'esprit, l'intelligence ou le raisonnement quelque chose");
	    Fast.put("manger", "Absorber un aliment");
	    Fast.put("boire", "Absorber, ingérer un liquide");
	    Fast.put("parler", "prononcer les sons, les mots du langage");
	    Fast.put("voir", "Percevoir quelqu'un, quelque chose par les yeux");
	    Fast.put("entendre", "Percevoir par l'ouïe");
	    Fast.put("toucher", "Mettre sa main, ses doigts au contact de quelque chose");
	    Fast.put("faire", "Constituer par son action, son travail, quelque chose de concret à partir d'éléments, ou le tirer du néant");
	    Fast.put("partir", "Prendre le départ, commencer un mouvement");
	    Fast.put("conduire", " Mener quelqu'un, un animal avec soi vers un lieu déterminé, les accompagner à pied ou avec un véhicule");
	}
	
	/*@Test
	void test() {
	    Assertions.assertFalse(Fast.isEmpty());
	}*/

}
