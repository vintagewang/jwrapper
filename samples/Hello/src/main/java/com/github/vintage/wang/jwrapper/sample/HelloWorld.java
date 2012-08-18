package com.github.vintage.wang.jwrapper.sample;

import java.util.Iterator;
import java.util.Map;
import java.util.Properties;

public class HelloWorld {
	public static void printAll() {
		Map m = System.getenv();
		for (Iterator it = m.keySet().iterator(); it.hasNext();) {
			String key = (String) it.next();
			String value = (String) m.get(key);
			System.out.println(key + ":" + value);
		}
		System.out.println("--------------------------------------");
		Properties p = System.getProperties();

		for (Iterator it = p.keySet().iterator(); it.hasNext();) {
			String key = (String) it.next();
			String value = (String) p.get(key);
			System.out.println(key + ":" + value);
		}
	}

	public static void main(String[] args) {
		int i = 0;
		for (String arg : args) {
			System.out.println("arg[" + i++ + "] = " + arg);
		}
		printAll();
		System.out.println(System.getenv("LD_LIBRARY_PATH"));
		System.out.println("Hello World!");
		System.exit(0);
	}
}
