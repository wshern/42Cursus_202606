class Plant:
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float
    ) -> None:
        self._name = name

        if height < 0:
            self._height = 0.0
            print(f"{name.capitalize()}: Error, height can't be negative")
        else:
            self._height = height

        if days < 0:
            self._days = 0
            print(f"{name.capitalize()}: Error, age can't be negative")
        else:
            self._days = days

        if grow_rate < 0:
            self._grow_rate = 0.0
            print(f"{name.capitalize()}: Error, growth rate can't be negative")
        else:
            self._grow_rate = grow_rate

    def show(self) -> None:
        print(f"{self._name.capitalize()}:", end=" ")
        print(f"{round(self._height, 1)}cm, {self._days} days old")

    def grow(self) -> None:
        self._height += self._grow_rate

    def age(self) -> None:
        self._days += 1

    def sim_growth(self) -> None:
        self.grow()
        self.age()
        self.show()

    def set_age(self, value: int) -> None:
        if value < 0:
            print(f"{self._name.capitalize()}: Error, age can't be negative")
            print("Age update rejected")
        else:
            self._days = value
            print(f"Age updated: {value} days")

    def set_height(self, value: float) -> None:
        if value < 0:
            print(f"{self._name.capitalize()}: "
                  "Error, height can't be negative")
            print("Height update rejected")
        else:
            self._height = value
            print(f"Height updated: {value}cm")

    def get_age(self) -> int:
        return self._days

    def get_height(self) -> float:
        return self._height


# child class
class Flower(Plant):
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float,
        colour: str
    ) -> None:
        super().__init__(name, height, days, grow_rate)
        self._color = colour
        self._isbloom = False

    def bloom(self) -> None:
        print(f"[asking the {self._name} to bloom]")
        self._isbloom = True

    def show(self) -> None:
        super().show()
        print(f"Color: {self._color}")
        if self._isbloom is True:
            print(f"{self._name.capitalize()} is blooming beautifully!")
        else:
            print(f"{self._name.capitalize()} has not bloomed yet")


class Tree(Plant):
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float,
        trunk_diameter: float
    ) -> None:
        super().__init__(name, height, days, grow_rate)
        self._trunk_diameter = trunk_diameter

    def produce_shade(self) -> None:
        print(f"[asking the {self._name} to produce shade]")
        print(f"Tree {self._name.capitalize()} now produces a shade of "
              f"{self._height}cm long and {self._trunk_diameter}cm wide.")

    def show(self) -> None:
        super().show()
        print(f"Trunk diameter: {self._trunk_diameter}cm")


class Vegetable(Plant):
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float,
        harvest_season: str,
        nutri_value: int,
        growth: int
    ) -> None:
        super().__init__(name, height, days, grow_rate)
        self._harvest_season = harvest_season
        self._nutri_value = nutri_value
        self._growth = growth

    def show(self) -> None:
        super().show()
        print(f"Harvest season: {self._harvest_season}")
        print(f"Nutritional value: {self._nutri_value}")

    def grow(self) -> None:
        super().grow()
        self._nutri_value += 1

    def sim_growth(self) -> None:
        print(f"[make {self._name} grow and age "
              f"for {self._growth} days]")
        for _ in range(self._growth):
            self.age()
            self.grow()
        self.show()


def main() -> None:
    print("=== Garden Plant Types ===")
    print("=== Flower")
    rose = Flower("rose", 15.0, 10, 0, "red")
    rose.show()
    rose.bloom()
    rose.show()
    print()

    print("=== Tree")
    oak = Tree("oak", 200.0, 365, 0.0, 5.0)
    oak.show()
    oak.produce_shade()
    print()

    print("=== Vegetable")
    tomato = Vegetable('tomato', 5.0, 10, 2.1, "April", 0, 20)
    tomato.show()
    tomato.sim_growth()


if __name__ == "__main__":
    main()
