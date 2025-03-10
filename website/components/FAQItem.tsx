'use client';
import { useState, useId, useRef, useEffect } from 'react';

interface FAQItemProps {
  question: string;
  answer: string;
}

export default function FAQItem({ question, answer }: FAQItemProps) {
  const [isOpen, setIsOpen] = useState(false);
  const [height, setHeight] = useState(0);
  const contentRef = useRef<HTMLDivElement>(null);
  const uniqueId = useId();
  const headingId = `faq-question-${uniqueId}`;
  const panelId = `faq-answer-${uniqueId}`;

  // Measure content height when it changes or when isOpen changes
  useEffect(() => {
    if (isOpen && contentRef.current) {
      setHeight(contentRef.current.scrollHeight);
    } else {
      setHeight(0);
    }
  }, [isOpen]);

  return (
    <div 
      itemScope 
      itemProp="mainEntity" 
      itemType="https://schema.org/Question"
      className="rounded-xl border border-zinc-800/50 bg-zinc-900/50 overflow-hidden transition-colors duration-200 hover:border-purple-600/30"
    >
      <button 
        onClick={() => setIsOpen(!isOpen)}
        className="flex w-full cursor-pointer items-center justify-between p-6 text-left text-white"
        aria-expanded={isOpen}
        aria-controls={panelId}
      >
        <h3 
          id={headingId}
          itemProp="name" 
          className="font-medium"
        >
          {question}
        </h3>
        <span 
          className={`ml-6 flex-shrink-0 text-purple-400 transform transition-transform duration-300 ${isOpen ? 'rotate-180' : 'rotate-0'}`}
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            className="h-6 w-6"
            fill="none"
            viewBox="0 0 24 24"
            stroke="currentColor"
            aria-hidden="true"
          >
            <path
              strokeLinecap="round"
              strokeLinejoin="round"
              strokeWidth="2"
              d="M19 9l-7 7-7-7"
            />
          </svg>
        </span>
      </button>
      
      <div 
        className="overflow-hidden transition-all duration-300 ease-in-out"
        style={{ height: `${height}px` }}
      >
        <div 
          ref={contentRef}
          itemScope 
          itemProp="acceptedAnswer" 
          itemType="https://schema.org/Answer"
          className="px-6 pb-6 pt-0"
          id={panelId}
          role="region"
          aria-labelledby={headingId}
        >
          <div 
            className={`text-zinc-400 transform transition-all duration-300 ${isOpen ? 'translate-y-0 opacity-100' : '-translate-y-3 opacity-0'}`}
          >
            <p itemProp="text">{answer}</p>
          </div>
        </div>
      </div>
    </div>
  );
}
