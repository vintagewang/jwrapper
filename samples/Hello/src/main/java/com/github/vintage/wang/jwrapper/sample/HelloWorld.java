package com.github.vintage.wang.jwrapper.sample;

public class HelloWorld {
	public static void main(String[] args) {
		int i = 0;
		for (String arg : args) {
			System.out.println("arg[" + i++ + "] = " + arg);
		}
		System.out.println("Hello World!");
		System.exit(0);
	}
}
