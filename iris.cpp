#include <iostream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#define PROJECT_NAME "iris"

int main(int argc, char **argv) {
    using namespace ftxui;
    if (argc != 1) {
        std::cout << argv[0] << " takes no arguments.\n";
        return 1;
    }
    std::cout << "This is project " << PROJECT_NAME << ".\n";

    Element document = hbox({
        text("left") | border,
	text("middle") | border | flex,
	text("right") | border,
    });


    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);
    screen.Print();

    return 0;
}
