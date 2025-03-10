import { formatDate } from "@/lib/utils";
// If Image is imported from next/image, rename it to NextImage
// import Image from "next/image";
// import { Image as NextImage } from "next/image";

<header className="mb-2 flex flex-wrap items-center justify-between gap-4">
  <h3 className="text-lg font-medium text-white">{update.title}</h3>
  <time
    dateTime={new Date(update.createdAt).toISOString()}
    className="text-sm text-zinc-500"
  >
    {formatDate(new Date(update.createdAt))}
  </time>
</header>
