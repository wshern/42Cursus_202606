class Plant:
    def __init__(
        self,
        name: str,
        height: float,
        days: int,
        grow_rate: float
    ) -> None:
        self.name: str = name
        self.height: float = height
        self.days: int = days
        self.grow_rate: float = grow_rate

    def show(self) -> None:
        print(f"{self.name}: {round(self.height, 1)}cm, {self.days} days old")

    def grow(self) -> None:
        self.height += self.grow_rate

    def age(self) -> None:
        self.days += 1

    def sim_growth(self) -> None:
        self.grow()
        self.age()
        self.show()


def main() -> None:
    rose = Plant("Rose", 25.0, 30, 0.8)
    oak = Plant("Oak", 200.0, 365, 0.0)
    cactus = Plant("Cactus", 5.0, 90, 0.0)
    sunflower = Plant("Sunflower", 80.0, 45, 0.0)
    fern = Plant("Fern", 15.0, 120, 0.0)

    plants = [rose, oak, cactus, sunflower, fern]

    print("=== Plant Factory Output ===")
    for plant in plants:
        print("Created:", end=" ")
        plant.show()


if __name__ == "__main__":
    main()
