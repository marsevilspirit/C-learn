#include <string>

struct Point2D
{
    int x{};
    int y{};
};

class Box{
public:
    void setTopLeft(Point2D point){m_topLeft = point;}
    void setBottomRight(Point2D point) {m_bottomRight = point;}

private:
    Point2D m_topLeft{};
    Point2D m_bottomRight{};
};

class Label{
public:
    void setText(const std::string_view str){m_text = str;}
    void setFontSize(int fontSize){m_fontSize = fontSize;}

private:
    std::string m_text{};
    int m_fontSize{};
};

class Tooltip{
public:
    void setText(const std::string_view str){m_text =str;}

private:
    std::string m_text{};
};

class Button: public Box, public Label, public Tooltip{};

int main(void)
{
    Button button{};
    button.Box::setTopLeft({1, 1});
    button.Box::setBottomRight({10, 10});
    button.Label::setText("Submit");
    button.Label::setFontSize(6);
    button.Tooltip::setText("Submit the form to the server");
}
