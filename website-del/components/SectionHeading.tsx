import React from 'react';

interface SectionHeadingProps {
  id: string;
  title: string;
  icon: string;
}

export default function SectionHeading({ id, title, icon }: SectionHeadingProps) {
  return (
    <h2 id={id} className="mb-8 flex items-center text-2xl font-bold text-white">
      <svg
        xmlns="http://www.w3.org/2000/svg"
        className="mr-2 h-6 w-6 text-purple-500"
        fill="none"
        viewBox="0 0 24 24"
        stroke="currentColor"
        aria-hidden="true"
      >
        <path
          strokeLinecap="round"
          strokeLinejoin="round"
          strokeWidth="2"
          d={icon}
        />
      </svg>
      {title}
    </h2>
  );
}
