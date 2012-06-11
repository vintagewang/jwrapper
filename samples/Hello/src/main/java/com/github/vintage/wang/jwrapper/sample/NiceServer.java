package com.github.vintage.wang.jwrapper.sample;

public class NiceServer {
	private final Thread threadHello;

	private final Thread threadNice;

	public NiceServer() {
		this.threadHello = new Thread(new Runnable() {

			@Override
			public void run() {
				for (int i = 0; i < 10; i++) {
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
				for (int i = 0; i < 10; i++) {
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
		System.out.println("NiceServer begin...");
		NiceServer niceServer = new NiceServer();
		niceServer.start();
		System.out.println("NiceServer end.");
	}

}
