#include <iostream>
#include <string>

class Message
{
private:
    std::string sendName;
    int         sendTime;

public:
    Message(int sendTime_in, std::string sendName_in)
        :sendTime{sendTime_in}, sendName{sendName_in}
    {}
    
    std::string getSendName() const { return sendName; }
    int getSentTime() const { return sendTime; }
    virtual std::string getContent() const = 0;
};

class TextMessage : public Message
{

private:
    std::string text;

public:
    TextMessage(int sendTime_in = 0, std::string sendName_in = "No name", std::string text_in = "No text.")
        :Message(sendTime_in, sendName_in), text{ text_in } 
    {}

    std::string Text() const { return text; }
    std::string getContent() const { return text; }
};

class Image
{
public:
    operator std::string() { return "Picture"; }
};

class ImageMessage : public Message
{
private:
    Image *p_image;

public:
    ImageMessage(int sendTime_in = 0, std::string sendName_in = "No name", Image *image_in = nullptr)
        :Message{ sendTime_in , sendName_in }, p_image{ image_in }
    {}

    Image* getImage() const { return p_image; }

    std::string getContent() const
    {
        return (std::string)(*p_image);
    }
};

void printMessage(const Message &m)
{
    std::cout << "Person : " << m.getSendName() << std::endl;
    std::cout << "Time   : " << m.getSentTime() << std::endl;
    std::cout << "Text   : " << m.getContent() << std::endl;
    std::cout << std::endl;
}

int main()
{
    Image *p_DogImage = new Image;

    Message *messages[] = {
    new TextMessage{ 10, "sbi", "hello!!" },
    new ImageMessage{ 20, "sbi", p_DogImage },
    new ImageMessage{ 20, "sbi", p_DogImage },
    new TextMessage{ 10, "sbi", "hello!!" }
    };


    for (auto &m : messages)
        printMessage(*m);

    for (auto &m : messages)
        delete m;

    delete p_DogImage;
} 