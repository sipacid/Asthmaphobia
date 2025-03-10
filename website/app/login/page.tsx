"use client";

import { login } from "@/app/actions/auth";
import { useActionState } from "react";
import Link from "next/link";

export default function Login() {
  const [state, action, pending] = useActionState(login, undefined);

  return (
    <div className="min-h-screen bg-black">
      <div className="relative">
        <div className="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"></div>
        <div className="flex min-h-[calc(100vh-64px)] items-center justify-center px-4 py-16 sm:px-6 lg:px-8">
          <div className="w-full max-w-md space-y-8">
            <div className="relative overflow-hidden rounded-3xl border border-zinc-800/40 bg-zinc-900/70 p-8 shadow-xl backdrop-blur-md">
              {/* Animation elements */}
              <div className="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"></div>
              <div className="absolute -inset-[500px] -z-10">
                <div className="absolute top-1/2 left-1/2 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px] animate-pulse"></div>
                <div className="absolute top-1/3 right-1/3 h-[400px] w-[400px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-blue-500/10 blur-[80px]"></div>
              </div>

              {/* Animated gradient border */}
              <div className="absolute inset-0 rounded-3xl bg-gradient-to-r from-purple-500/20 via-blue-500/20 to-purple-500/20 opacity-30 bg-[length:200%_100%] animate-gradient"></div>

              <div className="relative z-10">
                <div className="text-center">
                  <div className="mb-4 inline-block rounded-full bg-gradient-to-r from-purple-500/20 to-purple-700/20 px-4 py-1.5 backdrop-blur-sm">
                    <span className="text-sm font-medium text-purple-300">
                      Account Access
                    </span>
                  </div>
                  <h2 className="mb-4 text-3xl font-bold text-white">
                    <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
                      Sign in to continue
                    </span>
                  </h2>
                </div>

                <form className="mt-8 space-y-6" action={action}>
                  <div className="space-y-4">
                    <div>
                      <label
                        htmlFor="email"
                        className="block text-sm font-medium text-zinc-300"
                      >
                        Email
                      </label>
                      <div className="mt-1 relative group">
                        <div className="absolute inset-0 rounded-xl bg-gradient-to-r from-purple-500/50 to-blue-500/50 opacity-0 group-focus-within:opacity-100 transition-opacity blur-sm"></div>
                        <input
                          id="email"
                          name="email"
                          placeholder="Email"
                          className="relative block w-full rounded-xl border border-zinc-700/50 bg-zinc-800/50 px-4 py-3 text-white shadow-sm backdrop-blur-sm focus:border-purple-500 focus:outline-none focus:ring-1 focus:ring-purple-500 transition-all"
                        />
                        <div className="absolute right-3 top-1/2 -translate-y-1/2 text-zinc-500">
                          <svg
                            xmlns="http://www.w3.org/2000/svg"
                            className="h-5 w-5"
                            fill="none"
                            viewBox="0 0 24 24"
                            stroke="currentColor"
                          >
                            <path
                              strokeLinecap="round"
                              strokeLinejoin="round"
                              strokeWidth={2}
                              d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z"
                            />
                          </svg>
                        </div>
                      </div>
                      {state?.errors?.email && (
                        <p className="mt-2 text-sm text-red-400 flex items-center">
                          <svg
                            xmlns="http://www.w3.org/2000/svg"
                            className="h-4 w-4 mr-1"
                            fill="none"
                            viewBox="0 0 24 24"
                            stroke="currentColor"
                          >
                            <path
                              strokeLinecap="round"
                              strokeLinejoin="round"
                              strokeWidth={2}
                              d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                            />
                          </svg>
                          {state.errors.email}
                        </p>
                      )}
                    </div>

                    <div>
                      <div className="flex justify-between items-center">
                        <label
                          htmlFor="password"
                          className="block text-sm font-medium text-zinc-300"
                        >
                          Password
                        </label>
                        <Link
                          href="/forgot-password"
                          className="text-xs text-purple-400 hover:text-purple-300 transition-colors"
                        >
                          Forgot password?
                        </Link>
                      </div>
                      <div className="mt-1 relative group">
                        <div className="absolute inset-0 rounded-xl bg-gradient-to-r from-purple-500/50 to-blue-500/50 opacity-0 group-focus-within:opacity-100 transition-opacity blur-sm"></div>
                        <input
                          id="password"
                          name="password"
                          type="password"
                          className="relative block w-full rounded-xl border border-zinc-700/50 bg-zinc-800/50 px-4 py-3 text-white shadow-sm backdrop-blur-sm focus:border-purple-500 focus:outline-none focus:ring-1 focus:ring-purple-500 transition-all"
                        />
                        <div className="absolute right-3 top-1/2 -translate-y-1/2 text-zinc-500">
                          <svg
                            xmlns="http://www.w3.org/2000/svg"
                            className="h-5 w-5"
                            fill="none"
                            viewBox="0 0 24 24"
                            stroke="currentColor"
                          >
                            <path
                              strokeLinecap="round"
                              strokeLinejoin="round"
                              strokeWidth={2}
                              d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z"
                            />
                          </svg>
                        </div>
                      </div>
                      {state?.errors?.password && (
                        <div className="mt-2 text-sm text-red-400">
                          <p className="flex items-center">
                            <svg
                              xmlns="http://www.w3.org/2000/svg"
                              className="h-4 w-4 mr-1"
                              fill="none"
                              viewBox="0 0 24 24"
                              stroke="currentColor"
                            >
                              <path
                                strokeLinecap="round"
                                strokeLinejoin="round"
                                strokeWidth={2}
                                d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                              />
                            </svg>
                            Password must:
                          </p>
                          <ul className="list-disc pl-5 text-xs">
                            {state.errors.password.map((error) => (
                              <li key={error}>{error}</li>
                            ))}
                          </ul>
                        </div>
                      )}
                    </div>
                  </div>

                  <button
                    disabled={pending}
                    type="submit"
                    className="group relative flex w-full justify-center overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-3.5 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none disabled:opacity-70"
                  >
                    <div className="relative z-10 flex items-center justify-center">
                      {pending ? (
                        <>
                          <svg
                            className="animate-spin -ml-1 mr-2 h-4 w-4 text-white"
                            xmlns="http://www.w3.org/2000/svg"
                            fill="none"
                            viewBox="0 0 24 24"
                          >
                            <circle
                              className="opacity-25"
                              cx="12"
                              cy="12"
                              r="10"
                              stroke="currentColor"
                              strokeWidth="4"
                            ></circle>
                            <path
                              className="opacity-75"
                              fill="currentColor"
                              d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"
                            ></path>
                          </svg>
                          Signing in...
                        </>
                      ) : (
                        <>
                          <svg
                            xmlns="http://www.w3.org/2000/svg"
                            className="h-5 w-5 mr-2"
                            fill="none"
                            viewBox="0 0 24 24"
                            stroke="currentColor"
                          >
                            <path
                              strokeLinecap="round"
                              strokeLinejoin="round"
                              strokeWidth={2}
                              d="M11 16l-4-4m0 0l4-4m-4 4h14m-5 4v1a3 3 0 01-3 3H6a3 3 0 01-3-3V7a3 3 0 013-3h7a3 3 0 013 3v1"
                            />
                          </svg>
                          Sign In
                        </>
                      )}
                    </div>
                    <div className="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"></div>
                  </button>

                  <div className="text-center text-sm text-zinc-400">
                    Don&apos;t have an account?{" "}
                    <Link
                      href="/register"
                      className="text-purple-400 hover:text-purple-300 transition-colors"
                    >
                      Register now
                    </Link>
                  </div>
                </form>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
