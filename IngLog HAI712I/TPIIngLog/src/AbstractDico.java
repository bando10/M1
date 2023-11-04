
public abstract class AbstractDico implements IDictionary {
	protected int size;
	protected Object[] keys;
	protected Object[] values;
	
	AbstractDico(){
		this.keys = new Object[0];
		this.values = new Object[0];
		this.size = 0; 
	}
	
	public Object get(Object Key) {
		int i = indexOf(Key);
		Object valeur = i == -1 ? null : values[i];
		return valeur;
	}


	public IDictionary put(Object key, Object value) {
		int n = newIndexOf(key);
		keys[n] = key;
		values[n] = value;			
		return this;
	}


	public boolean isEmpty() {
		return this.size == 0;
	}

	public boolean containsKey(Object key) {
		return (indexOf(key) == -1 ? false : true);
	}

	public int size() {
		return this.size;
	}
	abstract int indexOf(Object Key);
	abstract int newIndexOf(Object Key);
}
