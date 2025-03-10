"use client";

import Link from "next/link";
import { useState } from "react";

// Mock data - in a real app, this would come from an API
const announcements = [
  {
    id: 1,
    title: "Major Update: v2.4.0 Now Available",
    content:
      "We've just released version 2.4.0 with improved ESP features, better ghost detection, and fixes for the latest Phasmophobia update. Download now!",
    date: "2023-10-15",
    priority: "high",
  },
  {
    id: 2,
    title: "Holiday Special: VIP Access",
    content:
      "For a limited time, get VIP access to all premium features at a 25% discount. Offer ends January 5th!",
    date: "2023-10-10",
    priority: "medium",
  },
  {
    id: 3,
    title: "Discord Server Upgrade",
    content:
      "We've upgraded our Discord server with new channels and bots. Join us for real-time support and exclusive tips!",
    date: "2023-10-05",
    priority: "low",
  },
];

const patchNotes = [
  {
    version: "v2.4.0",
    date: "2023-10-15",
    changes: [
      'Added support for the new Phasmophobia "Ascension" update',
      "Improved ESP features with better color coding for different ghost types",
      "Fixed crash issue when loading into larger maps",
      "Added new movement speed controls",
      "Optimized memory usage for better performance",
    ],
  },
  {
    version: "v2.3.5",
    date: "2023-09-20",
    changes: [
      "Fixed compatibility issues with the latest Phasmophobia patch",
      "Added new configuration options for ghost visibility",
      "Improved cheat enabling/disabling transitions",
      "Fixed rare crash when detecting multiple ghosts",
    ],
  },
];

const systemRequirements = {
  os: "Windows 10 (64-bit)",
  processor: "Intel Core i3-6100 / AMD Ryzen 3 1200",
  memory: "8 GB RAM",
  graphics: "NVIDIA GTX 760 / AMD Radeon R7 260x",
  directX: "Version 11",
  storage: "250 MB available space",
};

export default function Dashboard() {
  const [activeTab, setActiveTab] = useState<
    "announcements" | "patchNotes" | "sysreq"
  >("announcements");

  return (
    <div className="space-y-6">
      <div className="flex justify-between items-center">
        <h1 className="text-2xl font-bold text-white md:text-3xl">
          <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
            Welcome to Your Dashboard
          </span>
        </h1>

        {/* Download Button */}
        <Link
          href="#download-section"
          className="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-6 py-2 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
        >
          <div className="relative z-10 flex items-center justify-center">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              className="mr-2 h-5 w-5"
              fill="none"
              viewBox="0 0 24 24"
              stroke="currentColor"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth="2"
                d="M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-4l-4 4m0 0l-4-4m4 4V4"
              />
            </svg>
            Download Latest
          </div>
          <div className="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"></div>
        </Link>
      </div>

      {/* Status Cards */}
      <div className="space-y-4">
        {/* Success Status */}
        <div className="rounded-xl border border-green-800/30 bg-green-900/10 p-4 backdrop-blur-sm">
          <div className="flex items-center">
            <div className="flex h-10 w-10 items-center justify-center rounded-full bg-green-900/30">
              <svg
                xmlns="http://www.w3.org/2000/svg"
                className="h-6 w-6 text-green-400"
                fill="none"
                viewBox="0 0 24 24"
                stroke="currentColor"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth="2"
                  d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z"
                />
              </svg>
            </div>
            <div className="ml-3">
              <h3 className="text-lg font-medium text-green-400">
                Asthmaphobia v2.4.0 is ready for use
              </h3>
              <p className="text-sm text-green-200/70">
                Your cheat is up-to-date and compatible with the latest
                Phasmophobia version.
              </p>
            </div>
          </div>
        </div>

        {/* Warning about Antivirus */}
        <div className="rounded-xl border border-amber-800/30 bg-amber-900/10 p-4 backdrop-blur-sm">
          <div className="flex items-center">
            <div className="flex h-10 w-10 items-center justify-center rounded-full bg-amber-900/30">
              <svg
                xmlns="http://www.w3.org/2000/svg"
                className="h-6 w-6 text-amber-400"
                fill="none"
                viewBox="0 0 24 24"
                stroke="currentColor"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth="2"
                  d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"
                />
              </svg>
            </div>
            <div className="ml-3">
              <h3 className="text-base font-medium text-amber-400">
                Antivirus Warning
              </h3>
              <p className="text-sm text-amber-200/70">
                Some antivirus software may flag Asthmaphobia as malicious. This
                is a false positive. Add it to your exclusions list to prevent
                it from being quarantined.
              </p>
            </div>
          </div>
        </div>
      </div>

      {/* Tabs */}
      <div className="border-b border-zinc-800/40">
        <div className="-mb-px flex space-x-6">
          {[
            { id: "announcements", label: "Announcements" },
            { id: "patchNotes", label: "Patch Notes" },
            { id: "sysreq", label: "System Requirements" },
          ].map((tab) => (
            <button
              key={tab.id}
              onClick={() => setActiveTab(tab.id as any)}
              className={`py-2 px-1 border-b-2 font-medium transition-colors ${
                activeTab === tab.id
                  ? "border-purple-500 text-purple-400"
                  : "border-transparent text-zinc-500 hover:text-zinc-300 hover:border-zinc-500"
              }`}
            >
              {tab.label}
            </button>
          ))}
        </div>
      </div>

      {/* Announcements */}
      {activeTab === "announcements" && (
        <div className="space-y-4" id="announcements-section">
          {announcements.map((announcement) => (
            <div
              key={announcement.id}
              className={`rounded-xl border ${
                announcement.priority === "high"
                  ? "border-purple-800/40 bg-purple-900/10"
                  : announcement.priority === "medium"
                    ? "border-blue-800/40 bg-blue-900/10"
                    : "border-zinc-800/40 bg-zinc-900/50"
              } p-6 backdrop-blur-sm`}
            >
              <div className="flex flex-wrap items-center justify-between gap-2">
                <h3 className="text-lg font-medium text-white">
                  {announcement.title}
                </h3>
                <span className="text-sm text-zinc-500">
                  {announcement.date}
                </span>
              </div>
              <p className="mt-2 text-zinc-300">{announcement.content}</p>
            </div>
          ))}
        </div>
      )}

      {/* Patch Notes */}
      {activeTab === "patchNotes" && (
        <div className="space-y-6" id="patchnotes-section">
          {patchNotes.map((patch, index) => (
            <div
              key={index}
              className="rounded-xl border border-zinc-800/40 bg-zinc-900/50 p-6 backdrop-blur-sm"
            >
              <div className="mb-4 flex flex-wrap items-center justify-between gap-2">
                <h3 className="text-lg font-medium text-white">
                  <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
                    {patch.version}
                  </span>
                </h3>
                <span className="text-sm text-zinc-500">{patch.date}</span>
              </div>
              <ul className="space-y-2">
                {patch.changes.map((change, changeIndex) => (
                  <li key={changeIndex} className="flex text-zinc-300">
                    <span className="mr-2 text-purple-400">•</span>
                    {change}
                  </li>
                ))}
              </ul>
            </div>
          ))}
        </div>
      )}

      {/* System Requirements */}
      {activeTab === "sysreq" && (
        <div className="space-y-6" id="sysreq-section">
          {/* Only minimum requirements now */}
          <div className="rounded-xl border border-zinc-800/40 bg-zinc-900/50 p-6 backdrop-blur-sm">
            <h3 className="mb-4 text-lg font-medium text-white">
              <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
                System Requirements
              </span>
            </h3>
            <ul className="space-y-3">
              {Object.entries(systemRequirements).map(([key, value]) => (
                <li key={key} className="flex items-start">
                  <div className="flex h-5 w-5 items-center justify-center rounded-full bg-zinc-800 text-purple-400">
                    <svg
                      xmlns="http://www.w3.org/2000/svg"
                      className="h-3 w-3"
                      fill="none"
                      viewBox="0 0 24 24"
                      stroke="currentColor"
                    >
                      <path
                        strokeLinecap="round"
                        strokeLinejoin="round"
                        strokeWidth="2"
                        d="M5 13l4 4L19 7"
                      />
                    </svg>
                  </div>
                  <div className="ml-2">
                    <span className="text-xs font-medium uppercase text-zinc-500">
                      {key}:
                    </span>
                    <p className="text-zinc-300">{value}</p>
                  </div>
                </li>
              ))}
            </ul>
          </div>
        </div>
      )}

      {/* Download Section */}
      <div
        id="download-section"
        className="rounded-xl border border-zinc-800/40 bg-zinc-900/50 p-6 backdrop-blur-sm mt-6"
      >
        <h2 className="text-xl font-bold text-white mb-4">
          Download Asthmaphobia
        </h2>

        <div className="space-y-4">
          {/* Single download option */}
          <div className="rounded-lg border border-zinc-800/40 bg-zinc-900/80 p-4">
            <div className="flex items-center justify-between">
              <div>
                <h3 className="font-medium text-white">Latest Version</h3>
                <p className="text-sm text-zinc-400">v2.4.0</p>
              </div>
              <button className="rounded-lg bg-gradient-to-r from-purple-600 to-indigo-600 px-4 py-2 text-sm font-medium text-white hover:from-purple-500 hover:to-indigo-500 focus:outline-none">
                Download
              </button>
            </div>
          </div>

          <div className="rounded-lg border border-zinc-800/40 bg-zinc-900/80 p-4">
            <h3 className="font-medium text-white mb-2">
              Installation Instructions
            </h3>
            <ol className="list-decimal pl-5 text-zinc-300 text-sm space-y-1">
              <li>Download the latest version of Asthmaphobia</li>
              <li>Extract the ZIP file to any location on your computer</li>
              <li>Run Phasmophobia first and wait until it fully loads</li>
              <li>Run Asthmaphobia.exe as administrator</li>
              <li>
                Press{" "}
                <span className="bg-zinc-800 text-xs rounded px-2 py-0.5">
                  INSERT
                </span>{" "}
                in-game to open the menu
              </li>
            </ol>
          </div>
        </div>
      </div>
    </div>
  );
}
