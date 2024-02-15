class LivingCreature
{
public:
    int CurrentHitPoints;
    int MaximumHitPoints;

    LivingCreature(int currentHitPoints, int maximumHitPoints)
    {
        CurrentHitPoints = currentHitPoints;
        MaximumHitPoints = maximumHitPoints;
    }
    LivingCreature() = default;
};