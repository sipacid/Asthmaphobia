"use client";

import { ReactNode } from "react";
import Link from "next/link";
import { usePathname } from "next/navigation";

const navItems = [
  {
    name: "Overview",
    href: "/dashboard",
    icon: "M3 12l2-2m0 0l7-7 7 7M5 10v10a1 1 0 001 1h3m10-11l2 2m-2-2v10a1 1 0 01-1 1h-3m-6 0a1 1 0 001-1v-4a1 1 0 011-1h2a1 1 0 011 1v4a1 1 0 001 1m-6 0h6",
  },
  {
    name: "Downloads",
    href: "/dashboard/downloads",
    icon: "M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-4l-4 4m0 0l-4-4m4 4V4",
  },
  {
    name: "Settings",
    href: "/dashboard/settings",
    icon: "M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4",
  },
];

export default function DashboardLayout({ children }: { children: ReactNode }) {
  const pathname = usePathname();

  return (
    // Add padding-top to account for the fixed header
    <div className="min-h-screen bg-black pt-16">
      <div className="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"></div>

      <div className="relative z-10 flex min-h-[calc(100vh-64px)]">
        {/* Sidebar */}
        <div className="hidden w-64 border-r border-zinc-800/40 bg-zinc-900/70 backdrop-blur-md md:block">
          <div className="flex h-16 items-center justify-center border-b border-zinc-800/40">
            <h1 className="text-xl font-bold">
              <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
                Asthmaphobia
              </span>
            </h1>
          </div>

          <nav className="mt-6 px-2">
            <div className="space-y-1">
              {navItems.map((item) => {
                const isActive = pathname === item.href;

                return (
                  <Link
                    key={item.name}
                    href={item.href}
                    className={`group flex items-center rounded-lg px-3 py-2 transition-colors ${
                      isActive
                        ? "bg-purple-900/30 text-white"
                        : "text-zinc-400 hover:bg-zinc-800/50 hover:text-white"
                    }`}
                  >
                    <svg
                      xmlns="http://www.w3.org/2000/svg"
                      className={`mr-3 h-5 w-5 transition-colors ${
                        isActive
                          ? "text-purple-400"
                          : "text-zinc-500 group-hover:text-zinc-300"
                      }`}
                      fill="none"
                      viewBox="0 0 24 24"
                      stroke="currentColor"
                    >
                      <path
                        strokeLinecap="round"
                        strokeLinejoin="round"
                        strokeWidth={2}
                        d={item.icon}
                      />
                    </svg>
                    <span>{item.name}</span>
                  </Link>
                );
              })}
            </div>
          </nav>
        </div>

        {/* Main Content */}
        <main className="flex-1 overflow-y-auto pb-16">
          {/* Mobile Header */}
          <div className="border-b border-zinc-800/40 bg-zinc-900/70 backdrop-blur-md md:hidden">
            <div className="flex h-16 items-center justify-between px-4">
              <h1 className="text-lg font-bold">
                <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
                  Asthmaphobia
                </span>
              </h1>

              {/* Mobile menu button */}
              <button
                type="button"
                className="text-zinc-400 hover:text-white focus:outline-none"
              >
                <svg
                  xmlns="http://www.w3.org/2000/svg"
                  className="h-6 w-6"
                  fill="none"
                  viewBox="0 0 24 24"
                  stroke="currentColor"
                >
                  <path
                    strokeLinecap="round"
                    strokeLinejoin="round"
                    strokeWidth={2}
                    d="M4 6h16M4 12h16M4 18h16"
                  />
                </svg>
              </button>
            </div>
          </div>

          <div className="p-4 sm:p-6 md:p-8">{children}</div>
        </main>
      </div>
    </div>
  );
}
