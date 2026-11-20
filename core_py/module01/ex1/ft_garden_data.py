class Plant:
    def __init__(self, name: str, height: int, days: int) -> None:
        self.name: str = name
        self.height: int = height
        self.days: int = days

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.days} days old")


def main() -> None:
    rose = Plant("Rose", 25, 30)
    sunflower = Plant("Sunflower", 80, 45)
    cactus = Plant("Cactus", 15, 120)

    print("=== Garden Plant Registry ===")
    rose.show()
    sunflower.show()
    cactus.show()


if __name__ == "__main__":
    main()
