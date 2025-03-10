"use client";
import { useState, useEffect, useMemo, useCallback } from 'react';
import Image from 'next/image';
import Link from 'next/link';
import FAQItem from '@/components/FAQItem';
import { pageData } from '@/data/home-page-data';
import SectionHeading from '@/components/SectionHeading';

export default function Home() {
  const [heroAnimated, setHeroAnimated] = useState(false);
  const [visibleSections, setVisibleSections] = useState<{[key: string]: boolean}>({});
  const { screenshots, features, testimonials, updates, faqs } = useMemo(() => pageData, []);

  // Format date for updates
  const formatDate = useCallback((dateString: string) => {
    return new Date(dateString).toLocaleDateString(undefined, {
      year: 'numeric',
      month: 'short',
      day: 'numeric'
    });
  }, []);

  // Setup intersection observer for animation on scroll
  useEffect(() => {
    const observerOptions = {
      root: null,
      rootMargin: '0px',
      threshold: 0.15,
    };

    const sectionObserver = new IntersectionObserver((entries) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          setVisibleSections(prev => ({ 
            ...prev, 
            [entry.target.id]: true 
          }));
        }
      });
    }, observerOptions);

    const sections = document.querySelectorAll('section[id]');
    sections.forEach(section => {
      sectionObserver.observe(section);
    });

    return () => {
      sections.forEach(section => {
        sectionObserver.unobserve(section);
      });
    };
  }, []);

  // Trigger hero animation after component mounts
  useEffect(() => {
    setHeroAnimated(true);
    
    // Preload important images for better UX
    screenshots.forEach(screenshot => {
      // Use window.Image to explicitly reference the browser's native Image constructor
      const img = new window.Image();
      img.src = screenshot.src;
    });
  }, [screenshots]);

  return (
    <div className="min-h-screen bg-black">
      <div className="relative">
        <div className="absolute inset-0 bg-gradient-to-b from-purple-900/20 via-transparent to-transparent opacity-60"></div>
        <div className="relative z-10 container mx-auto max-w-6xl px-4 py-8">
          {/* Hero Section */}
          <section className="pt-16 pb-20" aria-labelledby="hero-heading">
            <div className="relative overflow-hidden rounded-3xl border border-zinc-800/40 bg-zinc-900/70 p-8 shadow-xl backdrop-blur-md md:p-12">
              <div className="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"></div>
              <div className="absolute -inset-[500px] -z-10">
                <div className="absolute top-1/2 left-1/2 h-[800px] w-[800px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px]"></div>
                <div className="absolute top-1/3 right-1/3 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-blue-500/10 blur-[120px]"></div>
              </div>

              <div className="relative z-10">
                <div className="flex flex-col items-center text-center">
                  <div className="mb-4 inline-block rounded-full bg-gradient-to-r from-purple-500/20 to-purple-700/20 px-4 py-1.5 backdrop-blur-sm">
                    <span className="text-sm font-medium text-purple-300">v2.4.0 — Latest Release</span>
                  </div>

                  <h1 id="hero-heading" 
                    className={`mb-4 text-5xl font-bold text-white transition-all duration-700 md:text-6xl ${heroAnimated ? 'scale-105' : ''}`}>
                    <span className="bg-gradient-to-r from-purple-400 to-blue-400 bg-clip-text text-transparent">
                      Asthmaphobia
                    </span>
                  </h1>

                  <p className={`mb-8 max-w-xl text-lg text-zinc-300 transition-all delay-200 duration-700
                    ${heroAnimated ? 'opacity-100 translate-y-0' : 'opacity-0 translate-y-4'}`}>
                    The most advanced and undetected cheat for Phasmophobia. Dominate the paranormal
                    realm with powerful ESP, movement hacks, and ghost control.
                  </p>

                  <div className={`mb-8 grid w-full max-w-3xl gap-6 transition-all delay-300 duration-700 md:grid-cols-3
                    ${heroAnimated ? 'opacity-100 translate-y-0' : 'opacity-0 translate-y-4'}`}>
                    {[
                      {
                        icon: "M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z",
                        title: "Undetected",
                        description: "Advanced stealth technology stays hidden from anti-cheat"
                      },
                      {
                        icon: "M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4",
                        title: "Feature-Rich",
                        description: "Over 30+ powerful features to enhance your gameplay"
                      },
                      {
                        icon: "M4 4v5h.582m15.356 2A8.001 8.001 0 004.582 9m0 0H9m11 11v-5h-.581m0 0a8.003 8.003 0 01-15.357-2m15.357 2H15",
                        title: "Constant Updates",
                        description: "Regular updates to match game patches and add new features"
                      }
                    ].map((item, index) => (
                      <div key={`hero-card-${index}`} className="flex flex-col items-center rounded-xl border border-zinc-800/50 bg-black/30 p-4 backdrop-blur-md">
                        <svg
                          xmlns="http://www.w3.org/2000/svg"
                          className="mb-2 h-7 w-7 text-purple-500"
                          fill="none"
                          viewBox="0 0 24 24"
                          stroke="currentColor"
                          aria-hidden="true"
                        >
                          <path
                            strokeLinecap="round"
                            strokeLinejoin="round"
                            strokeWidth="2"
                            d={item.icon}
                          />
                        </svg>
                        <h3 className="mb-1 font-semibold text-white">{item.title}</h3>
                        <p className="text-center text-sm text-zinc-400">
                          {item.description}
                        </p>
                      </div>
                    ))}
                  </div>

                  <div className={`mt-2 flex flex-col justify-center gap-4 transition-all delay-400 duration-700 sm:flex-row
                    ${heroAnimated ? 'opacity-100 translate-y-0' : 'opacity-0 translate-y-4'}`}>
                    <Link
                      href="/dashboard"
                      className="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-3.5 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
                      aria-label="Download latest version of Asthmaphobia"
                    >
                      <div className="relative z-10 flex items-center justify-center">
                        <svg
                          xmlns="http://www.w3.org/2000/svg"
                          className="mr-2 h-5 w-5"
                          fill="none"
                          viewBox="0 0 24 24"
                          stroke="currentColor"
                          aria-hidden="true"
                        >
                          <path
                            strokeLinecap="round"
                            strokeLinejoin="round"
                            strokeWidth="2"
                            d="M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-4l-4 4m0 0l-4-4m4 4V4"
                          />
                        </svg>
                        Download Latest Version
                      </div>
                      <div className="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"></div>
                    </Link>
                    <Link
                      href="/features"
                      className="rounded-xl border border-purple-700/50 bg-purple-900/10 px-8 py-3.5 text-center font-medium text-purple-300 backdrop-blur-sm transition-all hover:bg-purple-900/30 hover:text-purple-200 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
                      aria-label="View all Asthmaphobia features"
                    >
                      View All Features
                    </Link>
                  </div>
                </div>
              </div>
            </div>
          </section>

          {/* Screenshots Showcase */}
          <section 
            id="screenshots"
            className={`mb-16 transform transition-all duration-700 ${
              visibleSections.screenshots ? 'translate-y-0 opacity-100' : 'translate-y-10 opacity-0'
            }`} 
            aria-labelledby="screenshots-heading"
          >
            <SectionHeading 
              id="screenshots-heading"
              icon="M4 16l4.586-4.586a2 2 0 012.828 0L16 16m-2-2l1.586-1.586a2 2 0 012.828 0L20 14m-6-6h.01M6 20h12a2 2 0 002-2V6a2 2 0 00-2-2H6a2 2 0 00-2 2v12a2 2 0 002 2z"
              title="See It In Action"
            />

            <div className="grid gap-6 md:grid-cols-3">
              {screenshots.map((screenshot, index) => (
                <figure
                  key={`screenshot-${index}`}
                  className="group relative overflow-hidden rounded-xl border border-zinc-800/50 bg-zinc-900/50 shadow-lg transition-all hover:border-purple-600/30"
                >
                  <div className="absolute inset-0 z-10 bg-gradient-to-t from-black to-transparent opacity-0 transition-opacity group-hover:opacity-60"></div>
                  <div className="h-60 w-full overflow-hidden">
                    <Image
                      src={screenshot.src}
                      alt={screenshot.alt}
                      width={480}
                      height={270}
                      className="h-60 w-full object-cover transition-transform duration-500 group-hover:scale-105"
                      loading={index === 0 ? "eager" : "lazy"}
                      quality={85}
                      sizes="(max-width: 768px) 100vw, 33vw"
                    />
                  </div>
                  <figcaption className="absolute right-0 bottom-0 left-0 z-20 translate-y-full transform p-3 text-white transition-transform group-hover:translate-y-0">
                    <p className="text-sm font-medium">{screenshot.caption}</p>
                  </figcaption>
                </figure>
              ))}
            </div>
          </section>

          {/* Features Section */}
          <section 
            id="features"
            className={`mb-16 transform transition-all duration-700 ${
              visibleSections.features ? 'translate-y-0 opacity-100' : 'translate-y-10 opacity-0'
            }`} 
            aria-labelledby="features-heading"
          >
            <SectionHeading 
              id="features-heading"
              icon="M11 4a2 2 0 114 0v1a1 1 0 001 1h3a1 1 0 011 1v3a1 1 0 01-1 1h-1a2 2 0 100 4h1a1 1 0 011 1v3a1 1 0 01-1 1h-3a1 1 0 01-1-1v-1a2 2 0 10-4 0v1a1 1 0 01-1 1H7a1 1 0 01-1-1v-3a1 1 0 00-1-1H4a2 2 0 110-4h1a1 1 0 001-1V7a1 1 0 011-1h3a1 1 0 001-1V4z"
              title="Key Features"
            />

            <ul className="grid gap-6 sm:grid-cols-2 lg:grid-cols-4">
              {features.map((feature, index) => (
                <li
                  key={`feature-${index}`}
                  className="group rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-all duration-300 hover:scale-[1.02] hover:border-purple-600/30 hover:bg-zinc-900/70"
                >
                  <div className="mb-4 flex h-12 w-12 items-center justify-center rounded-lg bg-gradient-to-br from-purple-900/40 to-indigo-900/40 transition-colors duration-300 group-hover:from-purple-700/40 group-hover:to-indigo-600/40">
                    <svg
                      xmlns="http://www.w3.org/2000/svg"
                      className="h-6 w-6 text-purple-400 transition-colors duration-300 group-hover:text-purple-300"
                      fill="none"
                      viewBox="0 0 24 24"
                      stroke="currentColor"
                      aria-hidden="true"
                    >
                      <path
                        strokeLinecap="round"
                        strokeLinejoin="round"
                        strokeWidth="2"
                        d={feature.icon}
                      ></path>
                    </svg>
                  </div>
                  <h3 className="mb-2 text-lg font-medium text-white">{feature.title}</h3>
                  <p className="text-sm text-zinc-400 transition-colors duration-300 group-hover:text-zinc-300">
                    {feature.description}
                  </p>
                </li>
              ))}
            </ul>
          </section>

          {/* Testimonials */}
          <section 
            id="testimonials"
            className={`mb-16 transform transition-all duration-700 ${
              visibleSections.testimonials ? 'translate-y-0 opacity-100' : 'translate-y-10 opacity-0'
            }`} 
            aria-labelledby="testimonials-heading"
          >
            <SectionHeading 
              id="testimonials-heading"
              icon="M8 12h.01M12 12h.01M16 12h.01M21 12c0 4.418-4.03 8-9 8a9.863 9.863 0 01-4.255-.949L3 20l1.395-3.72C3.512 15.042 3 13.574 3 12c0-4.418 4.03-8 9-8s9 3.582 9 8z"
              title="What Users Say"
            />

            <ul className="grid gap-6 md:grid-cols-3">
              {testimonials.map((testimonial, index) => (
                <li
                  key={`testimonial-${index}`}
                  className="rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-transform hover:scale-[1.02] hover:border-purple-600/30"
                >
                  <div
                    className="mb-4 flex text-yellow-500"
                    aria-label={`${testimonial.rating} out of 5 stars`}
                  >
                    {Array.from({ length: 5 }, (_, i) => (
                      <svg
                        key={`star-${index}-${i}`}
                        xmlns="http://www.w3.org/2000/svg"
                        className={`h-5 w-5 ${i < testimonial.rating ? 'text-yellow-500' : 'text-zinc-700'}`}
                        viewBox="0 0 20 20"
                        fill="currentColor"
                        aria-hidden="true"
                      >
                        <path
                          d="M9.049 2.927c.3-.921 1.603-.921 1.902 0l1.07 3.292a1 1 0 00.95.69h3.462c.969 0 1.371 1.24.588 1.81l-2.8 2.034a1 1 0 00-.364 1.118l1.07 3.292c.3.921-.755 1.688-1.54 1.118l-2.8-2.034a1 1 0 00-1.175 0l-2.8 2.034c-.784.57-1.838-.197-1.539-1.118l1.07-3.292a1 1 0 00-.364-1.118l-2.799-2.034c-.784-.57-.38-1.81.588-1.81h3.461a1 1 0 00.951-.69l1.07-3.292z"
                        />
                      </svg>
                    ))}
                  </div>
                  <blockquote>
                    <p className="mb-4 text-zinc-300 italic">"{testimonial.content}"</p>
                    <cite className="text-sm font-medium text-purple-400 not-italic">
                      — {testimonial.author}
                    </cite>
                  </blockquote>
                </li>
              ))}
            </ul>
          </section>

          {/* Updates Section */}
          <section 
            id="updates"
            className={`mb-16 transform transition-all duration-700 ${
              visibleSections.updates ? 'translate-y-0 opacity-100' : 'translate-y-10 opacity-0'
            }`} 
            aria-labelledby="updates-heading"
          >
            <SectionHeading 
              id="updates-heading"
              icon="M13 10V3L4 14h7v7l9-11h-7z"
              title="Latest Updates"
            />

            <div className="space-y-4">
              {updates.map((update, index) => (
                <article
                  key={`update-${index}`}
                  className="rounded-xl border border-zinc-800/50 bg-zinc-900/50 p-6 backdrop-blur-sm transition-all hover:border-purple-600/30"
                >
                  <header className="mb-2 flex flex-wrap items-center justify-between gap-4">
                    <h3 className="text-lg font-medium text-white">{update.title}</h3>
                    <time
                      dateTime={new Date(update.createdAt).toISOString()}
                      className="text-sm text-zinc-500"
                    >
                      {formatDate(update.createdAt)}
                    </time>
                  </header>
                  <p className="text-zinc-400">{update.content}</p>
                </article>
              ))}
            </div>
          </section>

          {/* FAQ Section */}
          <section 
            id="faq"
            className={`mb-16 transform transition-all duration-700 ${
              visibleSections.faq ? 'translate-y-0 opacity-100' : 'translate-y-10 opacity-0'
            }`} 
            aria-labelledby="faq-heading"
          >
            <SectionHeading 
              id="faq-heading"
              icon="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
              title="Frequently Asked Questions"
            />

            <div className="space-y-4" itemScope itemType="https://schema.org/FAQPage">
              {faqs.map((faq, index) => (
                <FAQItem 
                  key={`faq-${index}`}
                  question={faq.question}
                  answer={faq.answer}
                />
              ))}
            </div>
          </section>

          {/* CTA Section */}
          <section 
            id="cta"
            className={`mb-4 transform transition-all duration-700 ${
              visibleSections.cta ? 'translate-y-0 opacity-100' : 'translate-y-10 opacity-0'
            }`}
          >
            <div className="relative overflow-hidden rounded-3xl border border-zinc-800/40">
              <div className="absolute inset-0 bg-gradient-to-r from-purple-900/20 to-blue-900/20 opacity-30"></div>
              <div className="absolute -inset-[500px] -z-10">
                <div className="absolute top-1/3 left-1/3 h-[600px] w-[600px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-purple-500/20 blur-[100px]"></div>
              </div>

              <div className="relative z-10 p-10 text-center md:p-16">
                <h2 className="mb-6 text-3xl font-bold text-white md:text-4xl">
                  Ready to Dominate Phasmophobia?
                </h2>
                <p className="mx-auto mb-8 max-w-2xl text-lg text-zinc-300">
                  Join ghost hunters using Asthmaphobia to enhance their gameplay experience. Get
                  instant access to all premium features.
                </p>

                <div className="flex flex-col items-center justify-center gap-4 sm:flex-row">
                  <Link
                    href="/dashboard"
                    className="group relative overflow-hidden rounded-xl bg-gradient-to-r from-purple-600 to-indigo-600 px-8 py-4 text-center font-medium text-white shadow-lg transition-all hover:from-purple-500 hover:to-indigo-500 focus:ring-2 focus:ring-purple-500 focus:ring-offset-2 focus:ring-offset-black focus:outline-none"
                  >
                    <div className="relative z-10 flex items-center justify-center">Get Started Now</div>
                    <div className="absolute inset-0 -translate-y-full bg-gradient-to-r from-purple-600/30 to-indigo-600/30 transition-transform duration-300 ease-out group-hover:translate-y-0"></div>
                  </Link>
                  <Link
                    href="/support"
                    className="rounded-xl border border-purple-700/50 bg-purple-900/10 px-8 py-4 text-center font-medium text-purple-300 backdrop-blur-sm transition-all hover:bg-purple-900/30 hover:text-purple-200 focus:ring-2 focus:ring-purple-500 focus:ring-offset-1 focus:ring-offset-black focus:outline-none"
                  >
                    Get Support
                  </Link>
                </div>
              </div>
            </div>
          </section>
        </div>
      </div>
    </div>
  );
}
