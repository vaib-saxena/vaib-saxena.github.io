using UnityEngine;
using MLAgents;

public class OfficeAcademy : Academy
{

    public float agentRunSpeed;
    public float agentRotationSpeed;
    public float spawnAreaMarginMultiplier;
    public Material goalScoredMaterial;
    public Material failMaterial;
    public float gravityMultiplier;
    void State()
    {
        Physics.gravity *= gravityMultiplier;
    }
}
