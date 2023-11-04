
public interface IDictionary {
	Object get(Object Key);
	IDictionary put(Object key, Object value);
	boolean isEmpty();
	boolean containsKey(Object key);
	int size();
}
