'use client';
import React, { useState, useEffect } from 'react';
import Link from 'next/link';

interface NavLink {
  href: string;
  label: string;
}

export default function NavLinks() {
  const [activeSection, setActiveSection] = useState<string>('');
  
  const navLinks: NavLink[] = [
    { href: '#screenshots', label: 'Screenshots' },
    { href: '#features', label: 'Features' },
    { href: '#testimonials', label: 'Testimonials' },
    { href: '#updates', label: 'Updates' },
    { href: '#faq', label: 'FAQ' },
  ];

  // Track active section on scroll
  useEffect(() => {
    const handleScroll = () => {
      const scrollPosition = window.scrollY + 100;
      
      const sections = document.querySelectorAll('section[id]');
      let currentSection = '';
      
      sections.forEach((section) => {
        const sectionTop = (section as HTMLElement).offsetTop;
        const sectionHeight = section.clientHeight;
        
        if (scrollPosition >= sectionTop && scrollPosition <= sectionTop + sectionHeight) {
          currentSection = section.id;
        }
      });
      
      setActiveSection(currentSection);
    };
    
    window.addEventListener('scroll', handleScroll);
    handleScroll();
    
    return () => {
      window.removeEventListener('scroll', handleScroll);
    };
  }, []);

  return (
    <nav className="hidden md:block">
      <ul className="flex space-x-6">
        {navLinks.map((link) => (
          <li key={link.href}>
            <Link
              href={link.href}
              className={`text-sm font-medium transition-colors ${
                activeSection === link.href.substring(1)
                  ? 'text-purple-400'
                  : 'text-zinc-400 hover:text-white'
              }`}
              onClick={(e) => {
                e.preventDefault();
                document.querySelector(link.href)?.scrollIntoView({ 
                  behavior: 'smooth' 
                });
              }}
            >
              {link.label}
            </Link>
          </li>
        ))}
      </ul>
    </nav>
  );
}
