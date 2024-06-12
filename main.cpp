#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
using namespace std;
// Enum for piece colors
bool isGameActive = true;
enum class Color { WHITE, BLACK }; 
const string imagePath = "./image/";
const string MAIN_BACKGROUND = ".\\image\\background_5.png";
const string INS_BACKGROUND = ".\\image\\background.png";
const int cellSize = 100;
const int boardSize = 8 * cellSize;  // 800x800 pixels
//forward declarations for classes
class Game;
class Queen; 
class Rook;
class Bishop;
class Knight;
class King;

//Class for main menu
class MainMenu { 
private:
    //Declarations for buttons
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font; 
    sf::RectangleShape playButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape instructionsButton; 
    sf::RectangleShape creditsButton; 
    sf::Text playButtonText;
    sf::Text exitButtonText;
    sf::Text instructionsButtonText; 
    sf::Text creditsButtonText; 

    //handle clicks
    void checkButtonClick(sf::Vector2i mousePos) {
        if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::PLAY;
        }
        else if (instructionsButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::INSTRUCTIONS;
        }
        else if (creditsButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::CREDITS;
        }
        else if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::EXIT;
        }
    }

    //draw buttons
    void drawButtons() {
        window.draw(playButton);
        window.draw(playButtonText);
        window.draw(exitButton);
        window.draw(exitButtonText);
        window.draw(instructionsButton); 
        window.draw(instructionsButtonText); 
        window.draw(creditsButton); 
        window.draw(creditsButtonText); 
    }

public:

    enum class MenuOption { NONE, PLAY, INSTRUCTIONS, CREDITS, EXIT };

    MenuOption selectedOption;

    MainMenu(sf::RenderWindow& window) : window(window), selectedOption(MenuOption::PLAY) {
        if (!backgroundTexture.loadFromFile(MAIN_BACKGROUND)) {
            std::cerr << "Failed to load background image" << std::endl;
            return;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }

        const int buttonWidth = 200;
        const int buttonHeight = 50;
        const sf::Color buttonBackgroundColor(200, 200, 200);
        const sf::Color buttonBorderColor = sf::Color::Red;

        // Initialize instructions button
        instructionsButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        instructionsButton.setFillColor(buttonBackgroundColor);
        instructionsButton.setOutlineColor(buttonBorderColor);
        instructionsButton.setOutlineThickness(2);
        instructionsButton.setPosition((window.getSize().x - buttonWidth) / 2, 150);

        instructionsButtonText.setFont(font);
        instructionsButtonText.setString("Instructions");
        instructionsButtonText.setCharacterSize(30);
        instructionsButtonText.setFillColor(sf::Color::Black);
        sf::FloatRect instructionsTextRect = instructionsButtonText.getLocalBounds();
        instructionsButtonText.setOrigin(instructionsTextRect.left + instructionsTextRect.width / 2.0f,
            instructionsTextRect.top + instructionsTextRect.height / 2.0f);
        instructionsButtonText.setPosition(instructionsButton.getPosition().x + instructionsButton.getSize().x / 2.0f,
            instructionsButton.getPosition().y + instructionsButton.getSize().y / 2.0f);

        // Initialize Play button
        playButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        playButton.setFillColor(buttonBackgroundColor);
        playButton.setOutlineColor(buttonBorderColor);
        playButton.setOutlineThickness(2);
        playButton.setPosition((window.getSize().x - buttonWidth) / 2, 100);

        playButtonText.setFont(font);
        playButtonText.setString("Play");
        playButtonText.setCharacterSize(30);
        playButtonText.setFillColor(sf::Color::Black);
        sf::FloatRect playTextRect = playButtonText.getLocalBounds();
        playButtonText.setOrigin(playTextRect.left + playTextRect.width / 2.0f,
            playTextRect.top + playTextRect.height / 2.0f);
        playButtonText.setPosition(playButton.getPosition().x + playButton.getSize().x / 2.0f,
            playButton.getPosition().y + playButton.getSize().y / 2.0f);

        // Initialize Exit button
        exitButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        exitButton.setFillColor(buttonBackgroundColor);
        exitButton.setOutlineColor(buttonBorderColor);
        exitButton.setOutlineThickness(2);
        exitButton.setPosition((window.getSize().x - buttonWidth) / 2, 200);

        exitButtonText.setFont(font);
        exitButtonText.setString("Exit");
        exitButtonText.setCharacterSize(30);
        exitButtonText.setFillColor(sf::Color::Black);
        sf::FloatRect exitTextRect = exitButtonText.getLocalBounds();
        exitButtonText.setOrigin(exitTextRect.left + exitTextRect.width / 2.0f,
            exitTextRect.top + exitTextRect.height / 2.0f);
        exitButtonText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2.0f,
            exitButton.getPosition().y + exitButton.getSize().y / 2.0f);

        // Initialize credits button
        creditsButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        creditsButton.setFillColor(buttonBackgroundColor);
        creditsButton.setOutlineColor(buttonBorderColor);
        creditsButton.setOutlineThickness(2);
        creditsButton.setPosition((window.getSize().x - buttonWidth) / 2, 250);

        creditsButtonText.setFont(font);
        creditsButtonText.setString("Credits");
        creditsButtonText.setCharacterSize(30);
        creditsButtonText.setFillColor(sf::Color::Black);
        sf::FloatRect creditsTextRect = creditsButtonText.getLocalBounds();
        creditsButtonText.setOrigin(creditsTextRect.left + creditsTextRect.width / 2.0f,
            creditsTextRect.top + creditsTextRect.height / 2.0f);
        creditsButtonText.setPosition(creditsButton.getPosition().x + creditsButton.getSize().x / 2.0f,
            creditsButton.getPosition().y + creditsButton.getSize().y / 2.0f);
    }

    void handleEvent(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            checkButtonClick(mousePos);
        }
    }


    void reset() {
        selectedOption = MenuOption::PLAY;
    }

    void draw() {
        window.draw(backgroundSprite);
        drawButtons();
    }

    bool isOpen() const {
        return selectedOption == MenuOption::NONE; // Check if menu is still open
    }

    void handleMouseClick(sf::Vector2i mousePos) {
        // Check if the mouse click is within the bounds of the buttons
        if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::PLAY;
        }
        else if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::EXIT;
        }
        else if (instructionsButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::INSTRUCTIONS;
        }
        else if (creditsButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = MenuOption::CREDITS;
        }
    }

    MenuOption getSelectedOption() const {
        return selectedOption;
    }
};


class ChessPiece {
public:
    sf::Sprite sprite;
    int x, y;
    Color color; // Enum for color

    ChessPiece(const sf::Texture& texture, int x, int y, Color color)
        : x(x), y(y), color(color) {
        sprite.setTexture(texture);
        float scale = static_cast<float>(cellSize) / texture.getSize().x;
        sprite.setScale(scale, scale);
        sprite.setPosition(x * cellSize, y * cellSize);
    }

    virtual ~ChessPiece() {}

    virtual int value() const = 0;
    virtual bool move(int toX, int toY, vector< unique_ptr<ChessPiece>>& pieces) = 0;
    virtual bool isValidMove(int toX, int toY, vector< unique_ptr<ChessPiece>>& pieces) const = 0;
    virtual bool isKing() const { return false; }

    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
        sprite.setPosition(x * cellSize, y * cellSize);
    }
};

int showPromotionUI(sf::RenderWindow& window, sf::Font& font) {
    // Ensure the font is loaded, consider moving this to the caller or ensure it's done before this function
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    sf::Text promotionText("Promote Pawn to:", font, 30);
    promotionText.setPosition(50, 50);
    promotionText.setFillColor(sf::Color::Black);

    sf::Text queenText("1. Queen", font, 25);
    queenText.setPosition(50, 100);
    queenText.setFillColor(sf::Color::Black);

    sf::Text rookText("2. Rook", font, 25);
    rookText.setPosition(50, 150);
    rookText.setFillColor(sf::Color::Black);

    sf::Text bishopText("3. Bishop", font, 25);
    bishopText.setPosition(50, 200);
    bishopText.setFillColor(sf::Color::Black);

    sf::Text knightText("4. Knight", font, 25);
    knightText.setPosition(50, 250);
    knightText.setFillColor(sf::Color::Black);

    // add a background
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(240, 240, 240)); // Light gray background

    // Main loop for the promotion window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (queenText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    return 1;
                }
                if (rookText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    return 2;
                }
                if (bishopText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    return 3;
                }
                if (knightText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    return 4;
                }
            }
        }

        window.clear(); // Clear with default or specified color
        window.draw(background); // Draw background
        window.draw(promotionText);
        window.draw(queenText);
        window.draw(rookText);
        window.draw(bishopText);
        window.draw(knightText);
        window.display();
    }
    return -1;
}


class Pawn : public ChessPiece {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    vector<sf::Texture>& textures; 
public:
    bool hasMoved;
    void promote(int x, int y, vector<unique_ptr<ChessPiece>>& pieces);
    int getTextureIndexForChoice(int choice);

    Pawn(const sf::Texture& texture, int x, int y, Color color, sf::RenderWindow& window, sf::Font& font, vector<sf::Texture>& textures)
        : ChessPiece(texture, x, y, color), window(window), font(font), textures(textures), hasMoved(false) {}
   

    bool move(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) {
        if (!isValidMove(toX, toY, pieces)) {
            return false;
        }

        // Check for capturing an enemy piece at the destination
        int targetIndex = -1;
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->x == toX && pieces[i]->y == toY) {
                targetIndex = i;
                break;
            }
        }

        // If there is an enemy piece at the destination
        if (targetIndex != -1) {
            if (pieces[targetIndex]->isKing()) {
                // King is captured, immediately end the game
                isGameActive = false;
                std::cout << ((pieces[targetIndex]->color == Color::WHITE) ? "White" : "Black")
                    << " king has been captured. Game over." << std::endl;
                pieces.erase(pieces.begin() + targetIndex);
                return true; // Stops further processing
            }
            if (pieces[targetIndex]->color != this->color) {
                pieces.erase(pieces.begin() + targetIndex);  // Remove the captured piece
            }
        }

        // Move the pawn to the new position
        setPosition(toX, toY);
        hasMoved = true;


        if (isGameActive && ((color == Color::WHITE && toY == 0) || (color == Color::BLACK && toY == 7))) {
            promote(toX, toY, pieces); // Only call promote if the game hasn't ended
        }
        return true;


    }

    int value() const override { return 1; }

    bool isValidMove(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) const {
        int direction = (color == Color::WHITE) ? -1 : 1;  // Direction of movement based on color

        // Move one square forward
        if (toX == x && toY == y + direction) {
            return !isPieceAt(toX, toY, pieces);
        }

        // Move two squares forward from the start position
        int startRow = (color == Color::WHITE) ? 6 : 1;
        if (!hasMoved && toX == x && toY == y + 2 * direction && y == startRow) {
            return !isPieceAt(x, y + direction, pieces) && !isPieceAt(toX, toY, pieces);
        }

        // Capture diagonally
        if (abs(toX - x) == 1 && toY == y + direction) {
            return isEnemyPieceAt(toX, toY, pieces);
        }

        return false;
    }

    bool isPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y) {
                return true;
            }
        }
        return false;
    }

    bool isEnemyPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y && piece->color != this->color) {
                return true;
            }
        }
        return false;
    }

};

class Knight : public ChessPiece {
public:
    Knight(const sf::Texture& texture, int x, int y, Color color)
        : ChessPiece(texture, x, y, color) {}

    bool move(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) override {
        if (!isValidMove(toX, toY, pieces)) {
            return false;
        }

        // Check for capturing an enemy piece at the destination
        int targetIndex = -1;
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->x == toX && pieces[i]->y == toY) {
                targetIndex = i;
                break;
            }
        }

        // If there is an enemy piece at the destination
        if (targetIndex != -1 && pieces[targetIndex]->color != this->color) {
            pieces.erase(pieces.begin() + targetIndex);  // Remove the captured piece
        }

        // Move the knight to the new position
        setPosition(toX, toY);
        return true;
    }

    int value() const override { return 3; }

    bool isValidMove(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) const override {
        int dx = abs(toX - x);
        int dy = abs(toY - y);

        // Knight moves in an "L" shape: 2 squares in one direction and 1 square in another
        if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
            return !isPieceAt(toX, toY, pieces) || isEnemyPieceAt(toX, toY, pieces);
        }
        return false;
    }

    bool isPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y) {
                return true;
            }
        }
        return false;
    }

    bool isEnemyPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y && piece->color != this->color) {
                return true;
            }
        }
        return false;
    }
};
class Bishop : public ChessPiece {
public:
    Bishop(const sf::Texture& texture, int x, int y, Color color)
        : ChessPiece(texture, x, y, color) {}

    int value() const override { return 3; }

    bool move(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) override {
        if (!isValidMove(toX, toY, pieces)) {
            return false;
        }

        // Check for capturing an enemy piece at the destination
        int targetIndex = -1;
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->x == toX && pieces[i]->y == toY) {
                targetIndex = i;
                break;
            }
        }

        // If there is an enemy piece at the destination
        if (targetIndex != -1 && pieces[targetIndex]->color != this->color) {
            pieces.erase(pieces.begin() + targetIndex);  // Remove the captured piece
        }

        // Move the bishop to the new position
        setPosition(toX, toY);
        return true;
    }
    bool isValidMove(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) const override {
        if (x == toX && y == toY) return false; // Bishop must move to a different position

        if (abs(toX - x) != abs(toY - y)) return false; // Must move diagonally

        int dx = (toX > x) ? 1 : -1;
        int dy = (toY > y) ? 1 : -1;
        int steps = abs(toX - x); // Number of squares to move

        for (int i = 1; i < steps; ++i) {
            if (isPieceAt(x + i * dx, y + i * dy, pieces)) {
                return false; // Path must be clear
            }
        }
        return !isPieceAt(toX, toY, pieces) || isEnemyPieceAt(toX, toY, pieces);
    }

    bool isPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y) {
                return true;
            }
        }
        return false;
    }

    bool isEnemyPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y && piece->color != this->color) {
                return true;
            }
        }
        return false;
    }
};


class Rook : public ChessPiece {
public:
    Rook(const sf::Texture& texture, int x, int y, Color color)
        : ChessPiece(texture, x, y, color) {}

    bool move(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) override {
        if (!isValidMove(toX, toY, pieces)) {
            return false;
        }

        // Check for capturing an enemy piece at the destination
        auto it = std::find_if(pieces.begin(), pieces.end(), [toX, toY, this](const unique_ptr<ChessPiece>& piece) {
            return piece->x == toX && piece->y == toY && piece->color != this->color;
            });

        // If an enemy piece is at the destination, capture it
        if (it != pieces.end()) {
            pieces.erase(it);
        }

        // Move the rook to the new position
        setPosition(toX, toY);
        return true;
    }


    int value() const override { return 5; }

    bool isValidMove(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) const override {
        if (x != toX && y != toY) {
            return false; // Rook moves along the x or y axis, not both
        }

        int stepX = (toX == x) ? 0 : (toX > x ? 1 : -1);
        int stepY = (toY == y) ? 0 : (toY > y ? 1 : -1);
        int steps = max(abs(toX - x), abs(toY - y));

        for (int i = 1; i < steps; ++i) {
            if (isPieceAt(x + i * stepX, y + i * stepY, pieces)) {
                return false; // Path must be clear of other pieces
            }
        }

        return true; // Path is clear, move is valid
    }

    bool isPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        return std::any_of(pieces.begin(), pieces.end(), [x, y](const unique_ptr<ChessPiece>& piece) {
            return piece->x == x && piece->y == y;
            });
    }

    bool isEnemyPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        return std::any_of(pieces.begin(), pieces.end(), [x, y, this](const unique_ptr<ChessPiece>& piece) {
            return piece->x == x && piece->y == y && piece->color != this->color;
            });
    }
};

class Queen : public ChessPiece {
public:
    Queen(const sf::Texture& texture, int x, int y, Color color)
        : ChessPiece(texture, x, y, color) {}

    bool move(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) override {
        if (!isValidMove(toX, toY, pieces)) {
            return false;
        }

        // Check for capturing an enemy piece at the destination
        int targetIndex = -1;
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->x == toX && pieces[i]->y == toY) {
                targetIndex = i;
                break;
            }
        }

        if (targetIndex != -1 && pieces[targetIndex]->color != this->color) {
            pieces.erase(pieces.begin() + targetIndex);  // Remove the captured piece
        }

        // Move the queen to the new position
        setPosition(toX, toY);
        return true;
    }

    int value() const override { return 9; }

    bool isValidMove(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) const override {
        int dx = toX - x;
        int dy = toY - y;
        if (dx != 0 && dy != 0 && abs(dx) != abs(dy)) return false; // Not a valid diagonal, rank, or file move

        int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
        int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);
        int steps = max(abs(dx), abs(dy));

        for (int i = 1; i < steps; ++i) {
            if (isPieceAt(x + i * stepX, y + i * stepY, pieces)) return false; // Path must be clear
        }
        return !isPieceAt(toX, toY, pieces) || isEnemyPieceAt(toX, toY, pieces);
    }

    bool isPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y) {
                return true;
            }
        }
        return false;
    }

    bool isEnemyPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y && piece->color != this->color) {
                return true;
            }
        }
        return false;
    }
};

class King : public ChessPiece {
public:
    King(const sf::Texture& texture, int x, int y, Color color)
        : ChessPiece(texture, x, y, color) {}

    bool isKing() const override { return true; }

    bool move(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) override {
        if (!isValidMove(toX, toY, pieces)) {
            return false;
        }

        // Check for capturing an enemy piece at the destination
        int targetIndex = -1;
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->x == toX && pieces[i]->y == toY) {
                targetIndex = i;
                break;
            }
        }

        if (targetIndex != -1 && pieces[targetIndex]->color != this->color) {
            pieces.erase(pieces.begin() + targetIndex);  // Remove the captured piece
        }

        // Move the king to the new position
        setPosition(toX, toY);
        return true;
    }

    int value() const override { return 0; }

    bool isValidMove(int toX, int toY, vector<unique_ptr<ChessPiece>>& pieces) const override {
        int dx = abs(toX - x);
        int dy = abs(toY - y);
        if (dx > 1 || dy > 1) return false; // King moves only one square in any direction

        // Ensure the destination is either unoccupied or occupied by an enemy piece
        return !isPieceAt(toX, toY, pieces) || isEnemyPieceAt(toX, toY, pieces);
    }

    bool isPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y) {
                return true;
            }
        }
        return false;
    }

    bool isEnemyPieceAt(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) const {
        for (const auto& piece : pieces) {
            if (piece->x == x && piece->y == y && piece->color != this->color) {
                return true;
            }
        }
        return false;
    }
}; 

class Game {
private:
    sf::RenderWindow window;
    vector<unique_ptr<ChessPiece>> pieces;
    vector<sf::Texture> textures;
    map<Color, int> scores;
    int selectedPieceIndex = -1;
    int selectedIndexX = 0, selectedIndexY = 0;
    bool isPieceSelected = false;
    const string imagePath = "./image/";
    const int cellSize = 100;
    const int boardSize = 8 * cellSize; // 800x800 pixels
    Color currentPlayer;
    sf::Font font;

public:
    Game() : window(sf::VideoMode(1100, 800), "Chess Game") {
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error loading the font
        }
        loadTextures();
        initializePieces();
        scores[Color::WHITE] = 0;
        scores[Color::BLACK] = 0;
    }
    Color getCurrentPlayer() const {
        return currentPlayer;
    }
    void initializePieces();
    void loadTextures();
    void highlightCell(int x, int y, bool isKingInCheck, int kingX, int kingY);
    void drawBoard();
    void drawUIPanel();
    void updateSelection(int& x, int& y, int dx, int dy);
    void togglePlayer();
    int findPieceAt(int x, int y);
    bool isCheckmate(Color kingColor);
    bool isKingInCheck(Color kingColor);
    bool isStalemate(Color kingColor);
    void movePiece(int x, int y, unique_ptr<ChessPiece>& selectedPiece);
    void updateGameStatus();
    void togglePieceSelection(int x, int y);
    void announceWinner(Color winner);
    bool kingExists(Color kingColor);
    void handleKeyPress(sf::Keyboard::Key key, int& x, int& y);
    void announceStalemate();
    void run();
};


int main() {

    Game game;
    game.run();
    return 0;
}

void Game::initializePieces() {
    // Assuming the textures are ordered as follows:
    // 0-5: Black pieces (bishop, king, knight, pawn, queen, rook)
    // 6-11: White pieces (bishop, king, knight, pawn, queen, rook)
    // Positions are set for a standard 8x8 chess board

    // Place pawns
    for (int i = 0; i < 8; ++i) {
        pieces.push_back(std::make_unique<Pawn>(textures[3], i, 1, Color::BLACK, window, font, textures));  // Black pawns
        pieces.push_back(std::make_unique<Pawn>(textures[9], i, 6, Color::WHITE, window, font, textures));  // White pawns
    }


    // Setup other pieces [Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook]
    vector<int> pieceOrder = { 5, 2, 0, 4, 1, 0, 2, 5 };  // Indexes for rook, knight, bishop, queen, king, bishop, knight, rook

    // Initialize black pieces
    for (int i = 0; i < 8; ++i) {
        if (i == 0 || i == 7) { // Rooks
            pieces.push_back(make_unique<Rook>(textures[pieceOrder[i]], i, 0, Color::BLACK));
        }
        else if (i == 1 || i == 6) { // Knights
            pieces.push_back(make_unique<Knight>(textures[pieceOrder[i]], i, 0, Color::BLACK));
        }
        else if (i == 2 || i == 5) { // Bishops
            pieces.push_back(make_unique<Bishop>(textures[pieceOrder[i]], i, 0, Color::BLACK));
        }
        else if (i == 3) { // Queen
            pieces.push_back(make_unique<Queen>(textures[pieceOrder[i]], i, 0, Color::BLACK));
        }
        else if (i == 4) { // King
            pieces.push_back(make_unique<King>(textures[pieceOrder[i]], i, 0, Color::BLACK));
        }
    }

    // Initialize white pieces
    for (int i = 0; i < 8; ++i) {
        if (i == 0 || i == 7) { // Rooks
            pieces.push_back(make_unique<Rook>(textures[pieceOrder[i] + 6], i, 7, Color::WHITE));
        }
        else if (i == 1 || i == 6) { // Knights
            pieces.push_back(make_unique<Knight>(textures[pieceOrder[i] + 6], i, 7, Color::WHITE));
        }
        else if (i == 2 || i == 5) { // Bishops
            pieces.push_back(make_unique<Bishop>(textures[pieceOrder[i] + 6], i, 7, Color::WHITE));
        }
        else if (i == 3) { // Queen
            pieces.push_back(make_unique<Queen>(textures[pieceOrder[i] + 6], i, 7, Color::WHITE));
        }
        else if (i == 4) { // King
            pieces.push_back(make_unique<King>(textures[pieceOrder[i] + 6], i, 7, Color::WHITE));
        }
    }
}
void Game::loadTextures() {
    textures.resize(12);
    const string pieceNames[12] = {
        "black_bishop.png", "black_king.png", "black_knight.png", "black_pawn.png", "black_queen.png", "black_rook.png",
        "white_bishop.png", "white_king.png", "white_knight.png", "white_pawn.png", "white_queen.png", "white_rook.png"
    };
    for (int i = 0; i < 12; ++i) {
        if (!textures[i].loadFromFile(imagePath + pieceNames[i])) {
            cerr << "Failed to load " << pieceNames[i] << endl;
            exit(1);
        }
    }
}


void Game::highlightCell(int x, int y, bool isKingInCheck, int kingX, int kingY) {
    sf::RectangleShape highlight(sf::Vector2f(100, 100)); // Assuming each cell is 100x100 pixels
    highlight.setPosition(x * 100, y * 100); // Set the position based on grid coordinates
    highlight.setFillColor(sf::Color::Transparent); // No fill
    if (isKingInCheck && x == kingX && y == kingY) {
        highlight.setOutlineColor(sf::Color::Blue); // Blue color if king is in check and this is the king's square
    }
    else {
        highlight.setOutlineColor(sf::Color::Red); // Red color for other squares
    }
    highlight.setOutlineThickness(5); // Thickness of the highlight border
    this->window.draw(highlight); // Draw the highlight on the window
}

void Game::drawBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            sf::RectangleShape rectangle(sf::Vector2f(100, 100));
            rectangle.setPosition(i * 100, j * 100);
            rectangle.setFillColor((i + j) % 2 == 0 ? sf::Color::White : sf::Color(100, 100, 100));
            window.draw(rectangle);
        }
    }
}
void Game::drawUIPanel() {
    // Background for the UI panel
    sf::RectangleShape uiBackground(sf::Vector2f(300, 800));
    uiBackground.setPosition(800, 0);
    uiBackground.setFillColor(sf::Color(240, 240, 240));
    window.draw(uiBackground);

    // Display the side text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Could not load font\n"; // Handle error appropriately
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // side text1
    text.setString("From Developers :) ");
    text.setPosition(810, 20);
    window.draw(text);

    // side text2
    text.setString("Have Fun Playing Game ");
    text.setPosition(810, 100);
    window.draw(text);

    // side text3
    text.setString("Best Of Luck! ");
    text.setPosition(810, 170);
    window.draw(text);
}

void Game::updateSelection(int& x, int& y, int dx, int dy) {
    int newX = x + dx;
    int newY = y + dy;
    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
        x = newX;
        y = newY;
    }
}

// for toggling the turn
void Game::togglePlayer() {
    currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

int Game::findPieceAt(int x, int y) {
    for (int i = 0; i < pieces.size(); ++i) {
        if (pieces[i]->x == x && pieces[i]->y == y) {
            return i;
        }
    }
    return -1; // No piece at this position
}

bool Game::isCheckmate(Color kingColor) { 
    if (!isKingInCheck(kingColor)) {
        return false; // Not a checkmate if the king is not in check
    }

    // Check if any move can remove the check
    for (auto& piece : pieces) {
        if (piece->color == kingColor) {
            int origX = piece->x;
            int origY = piece->y;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int newX = origX + dx;
                    int newY = origY + dy;
                    if (piece->isValidMove(newX, newY, pieces)) {
                        // Make the move temporarily
                        piece->setPosition(newX, newY);
                        bool wasKingInCheck = isKingInCheck(kingColor);
                        // Undo the move
                        piece->setPosition(origX, origY);
                        if (!wasKingInCheck) {
                            return false; // There is a valid move that removes the check
                        }
                    }
                }
            }
        }
    }
    return true; // No valid moves available, checkmate
}

bool Game::isKingInCheck(Color kingColor) {
    int kingX = -1, kingY = -1;
    // Find the king
    for (auto& piece : pieces) {
        if ((piece->isKing() && piece->color == kingColor)) {
            kingX = piece->x;
            kingY = piece->y;
            break;
        }
    }

    // Check for threats to the king
    for (auto& piece : pieces) {
        if (piece->color != kingColor && piece->isValidMove(kingX, kingY, pieces)) {
            return true; // King is in check
        }
    }
    return false;
}

bool Game::kingExists(Color kingColor) {
    for (const auto& piece : pieces) {
        if (typeid(*piece) == typeid(King) && piece->color == kingColor) {
            return true; // King is still on the board
        }
    }
    return false; // King is not on the board
}

bool Game::isStalemate(Color kingColor) { 
    if (isKingInCheck(kingColor)) {
        return false; // Not a stalemate if the king is in check
    }

    // Check if there are any legal moves available
    for (auto& piece : pieces) {
        if (piece->color == kingColor) {
            int origX = piece->x;
            int origY = piece->y;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int newX = origX + dx;
                    int newY = origY + dy;
                    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && piece->isValidMove(newX, newY, pieces)) {
                        // Make the move temporarily
                        piece->setPosition(newX, newY);
                        bool wasKingInCheck = isKingInCheck(kingColor);
                        // Undo the move
                        piece->setPosition(origX, origY);
                        if (!wasKingInCheck) {
                            return false; // There is at least one valid move
                        }
                    }
                }
            }
        }
    }
    std::cout << "Stalemate! The game is a draw." << std::endl;
    return true; // No valid moves available, stalemate
}

void Game::announceStalemate() {
    sf::Text stalemateText;
    stalemateText.setFont(font); // Assuming 'font' is loaded and available
    stalemateText.setCharacterSize(30);
    stalemateText.setFillColor(sf::Color::White);
    stalemateText.setString("Stalemate! The game is a draw.");
    stalemateText.setPosition(450, 350); // Adjust position based on your window settings

    // Display the stalemate text in the current window
    window.clear(sf::Color::Black);  // Clear the window with black color
    window.draw(stalemateText);         // Draw the stalemate text
    window.display();                // Display everything in the window

    // Pause to show the stalemate, then you can handle window closure or restart
    sf::sleep(sf::seconds(5));  // Pause for 5 seconds to show the stalemate

    // Optionally close the window or set up for a new game
    window.close();
}

void Game::movePiece(int x, int y, unique_ptr<ChessPiece>& selectedPiece) {
    int origX = selectedPiece->x;
    int origY = selectedPiece->y;

    // Find if there's a piece at the target location
    int targetIndex = findPieceAt(x, y);

    // Check if it's a valid move or a capture
    if (selectedPiece->isValidMove(x, y, pieces)) {
        if (targetIndex != -1) { // There's a piece to capture
            if (typeid(*pieces[targetIndex]) == typeid(King)) {
                // King is captured, end the game
                isGameActive = false;
                std::cout << ((pieces[targetIndex]->color == Color::WHITE) ? "White" : "Black")
                    << " king has been captured. Game over." << std::endl;
                pieces.erase(pieces.begin() + targetIndex); // Remove the captured king
                return; // End the move processing
            }
            if (pieces[targetIndex]->color != selectedPiece->color) {
                scores[selectedPiece->color] += pieces[targetIndex]->value(); // Update score
                pieces.erase(pieces.begin() + targetIndex); // Remove the captured piece
            }
        }

        // Move the piece
        selectedPiece->setPosition(x, y);
        if (!isGameActive) return; // Check if game ended due to king capture
        togglePlayer(); // Switch player turns
    }
    else {
        cout << "Invalid move." << endl;
    }
}


void Game::togglePieceSelection(int x, int y) {
    if (!isPieceSelected) {
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->x == x && pieces[i]->y == y && pieces[i]->color == currentPlayer) {
                selectedPieceIndex = i;
                isPieceSelected = true;
                return;
            }
        }
    }
    else {
        if (selectedPieceIndex != -1) {
            auto& selectedPiece = pieces[selectedPieceIndex];
            if (selectedPiece->color != currentPlayer) {
                std::cout << "Invalid move: Not your turn" << std::endl;
                return;
            }
            if (selectedPiece->isValidMove(x, y, pieces)) {
                // Check for captures, move the piece, etc.
                selectedPiece->move(x, y, pieces);

                togglePlayer();
            }
            updateGameStatus();
        }
        isPieceSelected = false;
    }
}

void Game::updateGameStatus() {
    if (!kingExists(Color::WHITE)) {  // If white king does not exist
        std::cout << "White king has been captured. Game over." << std::endl;
        announceWinner(Color::BLACK);  // Black wins
        isGameActive = false;
    }
    else if (!kingExists(Color::BLACK)) {  // If black king does not exist
        std::cout << "Black king has been captured. Game over." << std::endl;
        announceWinner(Color::WHITE);  // White wins
        isGameActive = false;
    }

    if (isCheckmate(currentPlayer)) {
        std::cout << (currentPlayer == Color::WHITE ? "White" : "Black") << " is in checkmate. Game over." << std::endl;
        announceWinner(currentPlayer == Color::WHITE ? Color::BLACK : Color::WHITE); // Announce the opposite player as winner
        isGameActive = false;
    }
    else if (isStalemate(currentPlayer)) {
        std::cout << "Stalemate. Game over." << std::endl;
        isGameActive = false; // End the game if stalemate is detected
        announceStalemate();
    }
}


void Game::handleKeyPress(sf::Keyboard::Key key, int& x, int& y) {
    int dx = 0, dy = 0;
    switch (key) {
    case sf::Keyboard::Up:    dy = -1; break;
    case sf::Keyboard::Down:  dy = 1; break;
    case sf::Keyboard::Left:  dx = -1; break;
    case sf::Keyboard::Right: dx = 1; break;
    case sf::Keyboard::Enter: togglePieceSelection(x, y); 
        return;
    }
    updateSelection(x, y, dx, dy);

}


void showInstructions(sf::RenderWindow& window, sf::Font& font) {
    // Create a new window for instructions
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(INS_BACKGROUND)) {
        // Handle error loading the background image
        return;
    }

    // Create a sprite for the background image
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    // Font for buttons

    // Instructions text with line wrapping
    sf::Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setPosition(20, 20);

    // Set line spacing and wrap text
    instructionsText.setLineSpacing(1.5);
    instructionsText.setString(
        "\n\n\n\n\nInstructions:\n"
        "- Objective: Checkmate opponent's king by capturing it.\n"
        "- Movement: Each piece moves uniquely, use the arrow keys and enter button for gameplay.\n"
        "- Capture: Pieces capture opponents by landing on their squares.\n"
        "- Special Rule - Check and Checkmate: King in check must be protected; checkmate ends the game.\n"
        "- Stalemate: No legal moves for a player not in check results in a draw.\n"
        "- Promotion: Pawns reaching the end can promote to any piece except king.\n"
    );

    const int buttonWidth = 200;
    const int buttonHeight = 50;

    sf::RectangleShape backButton(sf::Vector2f(buttonWidth, buttonHeight));
    backButton.setFillColor(sf::Color::Cyan);
    backButton.setOutlineThickness(2);
    backButton.setPosition((window.getSize().x - buttonWidth) / 2, 500); 

    sf::Text backText("Back", font, 30);
    backText.setFillColor(sf::Color::Black);
    backText.setPosition((window.getSize().x - backText.getLocalBounds().width) / 2,
        backButton.getPosition().y + (buttonHeight - backText.getLocalBounds().height) / 2);

    // Main loop for the instructions window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Check if Back button is clicked
                    if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        return; // Close the instructions window and return to the game
                    }
                }
            }
        }

        // Clear the instructions window
        window.clear();

        // Draw instructions text and background
        window.draw(backgroundSprite);
        window.draw(instructionsText);

        // Draw back button and text
        window.draw(backButton);
        window.draw(backText);

        // Display the contents of the instructions window
        window.display();
    }
}


void showCreditsWindow(sf::RenderWindow& window, sf::Font& font) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(INS_BACKGROUND)) {
        // Handle error loading the background image
        return;
    }

    // Create a sprite for the background image
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    // Credits text with line wrapping
    sf::Text creditsText;
    creditsText.setFont(font);
    creditsText.setCharacterSize(20);
    creditsText.setFillColor(sf::Color::Black);
    creditsText.setPosition(20, 20);

    // Set line spacing and wrap text
    creditsText.setLineSpacing(1.5);
    creditsText.setString(
        "\n\n\n\n\nCredits:\n"
        "- Name: Uma e Rubab\n"
        "  Roll No: 23L-0928.\n"
        "- Name: Ayesha Khalid.\n"
        "  Roll No: 23L-0667.\n"
    );

    const int buttonWidth = 200;
    const int buttonHeight = 50;

    sf::RectangleShape backButton(sf::Vector2f(buttonWidth, buttonHeight));
    backButton.setFillColor(sf::Color::Cyan);
    backButton.setOutlineThickness(2);
    backButton.setPosition((window.getSize().x - buttonWidth) / 2, 400);

    sf::Text backButtonText("Back", font, 30);
    backButtonText.setFillColor(sf::Color::Black);
    backButtonText.setPosition((window.getSize().x - backButtonText.getLocalBounds().width) / 2,
        backButton.getPosition().y + (buttonHeight - backButtonText.getLocalBounds().height) / 2);

    // Main loop for the credits window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Check if Back button is clicked
                    if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        return; // Close the credits window and return to the main menu
                    }
                }
            }
        }

        // Clear the main window
        window.clear();

        // Draw credits text and back button
        window.draw(backgroundSprite);
        window.draw(creditsText);
        window.draw(backButton);
        window.draw(backButtonText);

        // Display the contents of the main window
        window.display();
    }
}

void Game::announceWinner(Color winner) {
    // Preparing winner announcement text
    sf::Text winnerText;
    winnerText.setFont(font); // Assuming 'font' is loaded and available globally or passed as a parameter
    winnerText.setCharacterSize(30);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setString((winner == Color::WHITE ? "White Wins!" : "Black Wins!"));
    winnerText.setPosition(450, 350); // Adjust position based on your window settings

    // Display the winner text in the current window
    window.clear(sf::Color::Black);  // Clear the window with black color
    window.draw(winnerText);         // Draw the winner text
    window.display();                // Display everything in the window

    // Pause to show the winner, then you can handle window closure or restart
    sf::sleep(sf::seconds(5));  // Pause for 5 seconds to show the winner

    // Optionally close the window or set up for a new game
    window.close();
}

void Game::run() {
    bool isMainMenuActive = true;
    MainMenu mainMenu(window);

    while (window.isOpen() && isGameActive) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; // Exit the function and stop the game loop
            }

            if (isMainMenuActive) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // Pass the mouse click event to the main menu for button selection
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    mainMenu.handleMouseClick(mousePos);
                    if (mainMenu.getSelectedOption() == MainMenu::MenuOption::PLAY) {
                        isMainMenuActive = false; // Start the game
                    }
                    else if (mainMenu.getSelectedOption() == MainMenu::MenuOption::EXIT) {
                        window.close(); // Exit the game
                        return; // Exit the function and stop the game loop
                    }
                    else if (mainMenu.getSelectedOption() == MainMenu::MenuOption::INSTRUCTIONS) {
                        // Show instructions
                        showInstructions(window, font); // Pass window and font to showInstructions
                        isMainMenuActive = true; // Return to main menu after showing instructions
                    }
                    else if (mainMenu.getSelectedOption() == MainMenu::MenuOption::CREDITS) {
                        // Show credits
                        showCreditsWindow(window, font); // Pass font to showCreditsWindow
                        isMainMenuActive = true; // Return to main menu after showing credits
                    }
                }
            }
            else {
                if (event.type == sf::Event::KeyPressed) {
                    // Handle key events for the game
                    handleKeyPress(event.key.code, selectedIndexX, selectedIndexY);
                    // updateGameStatus();
                }
            }
        }

        window.clear(sf::Color::White);

        // Check if the current player's king is in check and get the king's position
        bool isKingCheck = isKingInCheck(currentPlayer);
        int kingX = -1, kingY = -1; // Initialize king's position variables
        if (isKingCheck) {
            // Find the king's position
            for (const auto& piece : pieces) {
                if (typeid(*piece) == typeid(King) && piece->color == currentPlayer) {
                    kingX = piece->x;
                    kingY = piece->y;
                    break;
                }
            }
        }

        if (isMainMenuActive) {
            mainMenu.draw();
        }
        else {
            drawBoard();
            drawUIPanel();
            for (const auto& piece : pieces) {
                window.draw(piece->sprite);
            }
            // highlightCell(selectedIndexX, selectedIndexY);
            highlightCell(selectedIndexX, selectedIndexY, isKingCheck, kingX, kingY);
        }

        window.display();
    }
}


void Pawn::promote(int x, int y, vector<unique_ptr<ChessPiece>>& pieces) {
    if (!isGameActive)
    {
        return;
    }// Do not continue if game is not active
    int choice = showPromotionUI(window, font);
    unique_ptr<ChessPiece> newPiece;

    // Load texture here, assuming textures are stored and accessible
    sf::Texture& texture = textures[getTextureIndexForChoice(choice)];

    switch (choice) {
    case 1:
        newPiece = std::make_unique<Queen>(texture, x, y, color);
        break;
    case 2:
        newPiece = std::make_unique<Rook>(texture, x, y, color);
        break;
    case 3:
        newPiece = std::make_unique<Bishop>(texture, x, y, color);
        break;
    case 4:
        newPiece = std::make_unique<Knight>(texture, x, y, color);
        break;
    }

    // Replace the pawn with the new piece
    for (int i = 0; i < pieces.size(); ++i) {
        if (pieces[i].get() == this) {
            pieces[i] = std::move(newPiece);
            break;
        }
    }
}

int Pawn::getTextureIndexForChoice(int choice) {
    int indexOffset = (color == Color::WHITE) ? 6 : 0; // Assuming the first 6 textures are black pieces and the next 6 are white pieces
    switch (choice) {
    case 1: return indexOffset + 4; // Queen
    case 2: return indexOffset + 5; // Rook
    case 3: return indexOffset + 0; // Bishop
    case 4: return indexOffset + 2; // Knight
    }
    return indexOffset; // Default to some safe value
}


