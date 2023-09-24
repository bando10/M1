package dictionary;

public class OrderedDictionary extends AbstractDico{

    OrderedDictionary(){
        super();
    }

    int indexOf(Object Key) {
        int j = -1, i = 0;
        for (Object x : this.keys) {
            if (x.equals(Key)){
                j = i;
            }
            i++;
        }
    return j;
    }

    int newIndexOf(Object Key){
        int n = this.size()+1;
        Object[] newKeys = new Object[n];
        Object[] newValues = new Object[n];
        for (int i = 0; i < n -1; i++){
            newKeys[i] = this.keys[i];
            newValues[i] = this.values[i];
        }
        this.keys = newKeys;
        this.values = newValues;
        this.size = n;

        return n-1;
    }
}