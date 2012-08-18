package com.github.vintage.wang.jwrapper.sample;

public class NiceServer {
	private final Thread threadHello;

	private final Thread threadNice;

	public NiceServer() {
		this.threadHello = new Thread(new Runnable() {

			@Override
			public void run() {
				for (int i = 0; i < 50; i++) {
					System.out.println(i + " Hello world");
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}, "Hello");

		this.threadNice = new Thread(new Runnable() {

			@Override
			public void run() {
				for (int i = 0; i < 50; i++) {
					System.out.println(i + " Nice world");
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}, "Nice");
	}

	public void start() {
		this.threadHello.start();
		this.threadNice.start();
	}

	public static void main(String[] args) {
		System.getProperties().list(System.out);
		System.out.println("-------------------------------------");
		System.out.println("maxMemory " + Runtime.getRuntime().maxMemory()/1024/1024);
		System.out.println("freeMemory " + Runtime.getRuntime().freeMemory()/1024/1024);
		System.out.println("totalMemory " + Runtime.getRuntime().totalMemory()/1024/1024);
		System.out.println("-------------------------------------");
		System.out.println("NiceServer begin...");
		NiceServer niceServer = new NiceServer();
		niceServer.start();
		System.out.println("NiceServer end.");
	}

}
