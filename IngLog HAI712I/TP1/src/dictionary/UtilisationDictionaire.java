package dictionary;
//import src.dictionary.IDictionary;

public class UtilisationDictionaire{
    public static void main(String[] args){
        IDictionary dic=new OrderedDictionary();
        System.out.println("Empty: "+dic.isEmpty()?"oui":"non");
        System.out.println("Size: "+dic.size());
        System.out.println("Contains key 1: "+(dic.containsKey(1)?"oui":"non)");
        System.out.println("Get(1): "+dic.get(1));
        dic.put(0,"Hola");
        dic.put(1,"Bonjour");
        dic.put(2,"Hello");
        dic.put(3,"Konnichiwa");

        System.out.println("Empty: "+dic.isEmpty()?"oui":"non");
        System.out.println("Size: "+dic.size());
        System.out.println("Contains key 1: "+dic.containsKey(1)?"oui":"non");
        System.out.println("Get(1): "+dic.get(1));

        }}


