import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";
import Header from "../components/Header";
import Footer from "../components/Footer";
import { getCurrentUser } from "@/data/user";

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "Asthmaphobia - Advanced Phasmophobia Cheat Software",
  description:
    "The ultimate Phasmophobia cheat with ESP, NoClip, Ghost Control, and 30+ advanced features. Undetected, constantly updated, and feature-rich.",
  keywords:
    "phasmophobia hack, asthmaphobia cheat, esp hack, noclip, ghost control, game cheats, ghost hunting tools",
};

export default async function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  const user = await getCurrentUser();

  return (
    <html lang="en">
      <head>
        <script
          crossOrigin="anonymous"
          src="//unpkg.com/react-scan/dist/auto.global.js"
        />
      </head>
      <body
        className={`${geistSans.variable} ${geistMono.variable} antialiased min-h-screen flex flex-col`}
      >
        <Header user={user} />

        <main className="flex-grow pt-16">{children}</main>

        <Footer />
      </body>
    </html>
  );
}
