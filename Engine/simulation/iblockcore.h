#ifndef IBLOCKCORE_H
#define IBLOCKCORE_H


namespace Simulation
{
    class IStepContext;

    class IBlockCore
    {
    public:
        virtual ~IBlockCore() {}

        virtual void execute(IStepContext*) = 0;
    };
}

Q_DECLARE_INTERFACE(Simulation::IBlockCore, "org.Simulate.Engine.IBlockCore/1.0")

#endif // IBLOCKCORE_H
