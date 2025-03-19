import { defineCollection, z } from "astro:content";
import { file } from "astro/loaders";

const news = defineCollection({
  loader: file("src/data/news.json"),
  schema: z.object({
    id: z.number(),
    title: z.string(),
    date: z.coerce.date(),
    category: z.string(),
    version: z.string().optional(),
    content: z.array(z.string()),
  }),
});

const faqs = defineCollection({
  loader: file("src/data/faqs.json"),
  schema: z.object({
    id: z.string(),
    items: z.array(
      z.object({
        question: z.string(),
        answer: z.string(),
      }),
    ),
  }),
});

const features = defineCollection({
  loader: file("src/data/features.json"),
  schema: z.object({
    id: z.string(),
    icon: z.string(),
    description: z.string(),
    features: z.array(
      z.object({
        title: z.string(),
        description: z.string(),
      }),
    ),
  }),
});

export const collections = { news, faqs, features };
