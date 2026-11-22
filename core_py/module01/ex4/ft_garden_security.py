class Plant:
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float
    ) -> None:
        self._name: str = name

        if height < 0:
            self._height = 0.0
            print(f"{name}: Error, height can't be negative")
        else:
            self._height = height

        if days < 0:
            self._days = 0
            print(f"{name}: Error, age can't be negative")
        else:
            self._days = days

        if grow_rate < 0:
            self._grow_rate = 0.0
            print(f"{name}: Error, growth rate can't be negative")
        else:
            self._grow_rate = grow_rate

    def show(self) -> None:
        print(f"{self._name}:", end=" ")
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
            print(f"{self._name}: Error, age can't be negative")
            print("Age update rejected")
        else:
            self._days = value
            print(f"Age updated: {value} days")

    def set_height(self, value: float) -> None:
        if value < 0:
            print(f"{self._name}: Error, height can't be negative")
            print("Height update rejected")
        else:
            self._height = value
            print(f"Height updated: {value}cm")

    def get_age(self) -> int:
        return self._days

    def get_height(self) -> float:
        return self._height


def main() -> None:
    print("=== Garden Security System ===")

    rose = Plant("Rose", 15.0, 10, 0.8)
    rose_height = 25.0
    rose_age = 30

    print("Plant created:", end=" ")
    rose.show()
    rose.set_height(rose_height)
    rose.set_age(rose_age)
    print("Current state: Rose:", end=" ")
    print(f"{rose.get_height()}cm, {rose.get_age()} days old")

    print()
    sunflower = Plant("Sunflower", -10.0, -5, -0.3)
    sun_height = -3.0
    sun_age = 3

    print()
    print("Plant created:", end=" ")
    sunflower.show()
    sunflower.set_height(sun_height)
    sunflower.set_age(sun_age)
    print("Current state:", end=" ")
    sunflower.show()


if __name__ == "__main__":
    main()
