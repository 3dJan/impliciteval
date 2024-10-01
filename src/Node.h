#include <functional>
#include <variant>
#include <stdexcept>

namespace impliciteval
{
    class Node;

    struct float3
    {
        double x, y, z;
    };

    struct Matrix4x4
    {
        double m[4][4];
    };

    using ExpressionResult = std::variant<double, float3, Matrix4x4>;
    class Input
    {
    public:
        std::function<ExpressionResult()> evaluateFunction;
    };

    class Node
    {
    private:
        /* data */
    public:
        Node(/* args */);
        ~Node();
    };

    class AddNode : public Node
    {
    public:
        AddNode(Input a, Input b)
            : m_inputA(a), m_inputB(b)
        {
        }

        ExpressionResult evalResult()
        {
            auto a = m_inputA.evaluateFunction();
            auto b = m_inputB.evaluateFunction();
            if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
            {
                return std::get<double>(a) + std::get<double>(b);
            }
            else if (std::holds_alternative<float3>(a) && std::holds_alternative<float3>(b))
            {
                auto a3 = std::get<float3>(a);
                auto b3 = std::get<float3>(b);
                return float3{a3.x + b3.x, a3.y + b3.y, a3.z + b3.z};
            }
            else if (std::holds_alternative<Matrix4x4>(a) && std::holds_alternative<Matrix4x4>(b))
            {
                auto a4 = std::get<Matrix4x4>(a);
                auto b4 = std::get<Matrix4x4>(b);
                Matrix4x4 result;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        result.m[i][j] = a4.m[i][j] + b4.m[i][j];
                    }
                }
                return result;
            }
            else
            {
                throw std::runtime_error("Invalid types for AddNode");
            }
        }

    private:
        Input m_inputA;
        Input m_inputB;
    };
} // namespace impliciteval
