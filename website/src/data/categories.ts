export interface Category {
  id: string;
  icon: string;
  description: string;
}

export const categories: Category[] = [
  {
    id: "Visuals",
    icon: "visuals",
    description:
      "Enhance your visual experience with ESP, ghost detection, and more",
  },
  {
    id: "Movement",
    icon: "movement",
    description:
      "Advanced movement features including teleportation and speed control",
  },
  {
    id: "Ghost Manipulation",
    icon: "ghostManipulation",
    description: "Control and interact with ghosts in various ways",
  },
  {
    id: "Player Abilities",
    icon: "playerAbilities",
    description: "Special abilities and enhancements for your character",
  },
  {
    id: "Cursed Items",
    icon: "cursedItems",
    description: "Features related to cursed items and their effects",
  },
  {
    id: "Miscellaneous",
    icon: "miscellaneous",
    description: "Additional features and utilities",
  },
];
