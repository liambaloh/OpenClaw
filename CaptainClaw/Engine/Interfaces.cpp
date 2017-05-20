#include "Interfaces.h"
#include "Logger/Logger.h"
#include "Util/StringUtil.h"

//=============================================================================
// ActorPrototype
//=============================================================================

std::string EnumToString_ActorPrototype(ActorPrototype actorProto)
{
    static std::map<ActorPrototype, std::string> actorPrototypeEnumToStringMap =
    {
        // Actor enemies
        { ActorPrototype_BaseEnemy, "ActorPrototype_BaseEnemy" },

        { ActorPrototype_Level1_Soldier, "ActorPrototype_Level1_Soldier" },
        { ActorPrototype_Level1_Officer, "ActorPrototype_Level1_Officer" },
        { ActorPrototype_Level1_Rat, "ActorPrototype_Level1_Rat" },
        { ActorPrototype_Level2_Soldier, "ActorPrototype_Level2_Soldier" },
        { ActorPrototype_Level2_Officer, "ActorPrototype_Level2_Officer" },
        { ActorPrototype_Level2_PunkRat, "ActorPrototype_Level2_PunkRat" },

        // Elevators
        { ActorPrototype_BaseElevator, "ActorPrototype_BaseElevator" },

        { ActorPrototype_Level1_Elevator, "ActorPrototype_Level1_Elevator" },
        { ActorPrototype_Level2_Elevator, "ActorPrototype_Level2_Elevator" },

        // Toggle pegs
        { ActorPrototype_BaseTogglePeg, "ActorPrototype_BaseTogglePeg" },

        { ActorPrototype_Level1_TogglePeg, "ActorPrototype_Level1_TogglePeg" },
        { ActorPrototype_Level2_TogglePeg, "ActorPrototype_Level2_TogglePeg" },

        // Projectile spawners
        { ActorPrototype_Level2_TowerCannonLeft, "ActorPrototype_Level2_TowerCannonLeft" },
        { ActorPrototype_Level2_TowerCannonRight, "ActorPrototype_Level2_TowerCannonRight" },

        // Projectiles
        { ActorPrototype_Level2_CannonBall, "ActorPrototype_Level2_CannonBall" },
        { ActorPrototype_Level2_RatProjectile, "ActorPrototype_Level2_RatProjectile" },

        // Boss Stagers
        { ActorPrototype_Level2_BossStager, "ActorPrototype_Level2_BossStager" },

        // Bosses
        { ActorPrototype_Level2_LaRaux, "ActorPrototype_Level2_LaRaux" },
        
        //=======================================
        // General
        //=======================================

        { ActorPrototype_BaseProjectile, "ActorPrototype_BaseProjectile" },
        { ActorPrototype_FireSwordProjectile, "ActorPrototype_FireSwordProjectile" },
        { ActorPrototype_FrostSwordProjectile, "ActorPrototype_FrostSwordProjectile" },
        { ActorPrototype_LightningSwordProjectile, "ActorPrototype_LightningSwordProjectile" },

        { ActorPrototype_BaseProjectileSpawner, "ActorPrototype_BaseProjectileSpawner" },

        // Sound
        { ActorPrototype_LocalAmbientSound, "ActorPrototype_LocalAmbientSound" },

        { ActorPrototype_BaseBossStager, "ActorPrototype_BaseBossStager" },

        //=======================================
        // Menu
        //=======================================

        { ActorPrototype_StaticImage, "ActorPrototype_StaticImage" },
        { ActorPrototype_StaticAnimatedImage, "ActorPrototype_StaticAnimatedImage" },
    };

    auto findIt = actorPrototypeEnumToStringMap.find(actorProto);
    if (findIt == actorPrototypeEnumToStringMap.end())
    {
        LOG_ERROR("Could not find actor enum: " + ToStr((int)actorProto));
        assert(false && "Could not convert ActorPrototype enum to string");
    }

    return findIt->second;
}

ActorPrototype StringToEnum_ActorPrototype(std::string actorProtoStr)
{
    static std::map<std::string, ActorPrototype> actorPrototypeStringToEnumMap =
    {
        // Actor enemies
        { "ActorPrototype_BaseEnemy", ActorPrototype_BaseEnemy },

        { "ActorPrototype_Level1_Soldier", ActorPrototype_Level1_Soldier },
        { "ActorPrototype_Level1_Officer", ActorPrototype_Level1_Officer },
        { "ActorPrototype_Level1_Rat", ActorPrototype_Level1_Rat },
        { "ActorPrototype_Level2_Soldier", ActorPrototype_Level2_Soldier },
        { "ActorPrototype_Level2_Officer", ActorPrototype_Level2_Officer },
        { "ActorPrototype_Level2_PunkRat", ActorPrototype_Level2_PunkRat },

        // Elevators
        { "ActorPrototype_BaseElevator", ActorPrototype_BaseElevator },

        { "ActorPrototype_Level1_Elevator", ActorPrototype_Level1_Elevator },
        { "ActorPrototype_Level2_Elevator", ActorPrototype_Level2_Elevator },

        // Toggle pegs
        { "ActorPrototype_BaseTogglePeg", ActorPrototype_BaseTogglePeg },

        { "ActorPrototype_Level1_TogglePeg", ActorPrototype_Level1_TogglePeg },
        { "ActorPrototype_Level2_TogglePeg", ActorPrototype_Level2_TogglePeg },

        // Projectile spawners
        { "ActorPrototype_Level2_TowerCannonLeft", ActorPrototype_Level2_TowerCannonLeft },
        { "ActorPrototype_Level2_TowerCannonRight", ActorPrototype_Level2_TowerCannonRight },

        // Projectiles
        { "ActorPrototype_Level2_CannonBall", ActorPrototype_Level2_CannonBall },
        { "ActorPrototype_Level2_RatProjectile", ActorPrototype_Level2_RatProjectile },

        // Boss Stagers
        { "ActorPrototype_Level2_BossStager", ActorPrototype_Level2_BossStager },

        // Bosses
        { "ActorPrototype_Level2_LaRaux", ActorPrototype_Level2_LaRaux },

        //=======================================
        // General
        //=======================================

        { "ActorPrototype_BaseProjectile", ActorPrototype_BaseProjectile },
        { "ActorPrototype_FireSwordProjectile", ActorPrototype_FireSwordProjectile },
        { "ActorPrototype_FrostSwordProjectile", ActorPrototype_FrostSwordProjectile },
        { "ActorPrototype_LightningSwordProjectile", ActorPrototype_LightningSwordProjectile },

        { "ActorPrototype_BaseProjectileSpawner", ActorPrototype_BaseProjectileSpawner },

        // Sound
        { "ActorPrototype_LocalAmbientSound", ActorPrototype_LocalAmbientSound },

        { "ActorPrototype_BaseBossStager", ActorPrototype_BaseBossStager },

        //=======================================
        // Menu
        //=======================================

        { "ActorPrototype_StaticImage", ActorPrototype_StaticImage },
        { "ActorPrototype_StaticAnimatedImage", ActorPrototype_StaticAnimatedImage },
    };

    auto findIt = actorPrototypeStringToEnumMap.find(actorProtoStr);
    if (findIt == actorPrototypeStringToEnumMap.end())
    {
        LOG_ERROR("Could not find actor enum: " + actorProtoStr);
        assert(false && "Could not convert ActorPrototype enum to string");
    }

    return findIt->second;
}

//=============================================================================
// FixtureType
//=============================================================================

FixtureType FixtureTypeStringToEnum(std::string fixtureTypeStr)
{
    FixtureType fixtureType = FixtureType_None;

    if (fixtureTypeStr == "Solid") { fixtureType = FixtureType_Solid; }
    else if (fixtureTypeStr == "Ground") { fixtureType = FixtureType_Ground; }
    else if (fixtureTypeStr == "Climb") { fixtureType = FixtureType_Climb; }
    else if (fixtureTypeStr == "Death") { fixtureType = FixtureType_Death; }
    else if (fixtureTypeStr == "Trigger") { fixtureType = FixtureType_Trigger; }
    else if (fixtureTypeStr == "Projectile") { fixtureType = FixtureType_Projectile; }
    else if (fixtureTypeStr == "Crate") { fixtureType = FixtureType_Crate; }
    else if (fixtureTypeStr == "Pickup") { fixtureType = FixtureType_Pickup; }
    else if (fixtureTypeStr == "Trigger") { fixtureType = FixtureType_Trigger; }
    else if (fixtureTypeStr == "Controller") { fixtureType = FixtureType_Controller; }
    else if (fixtureTypeStr == "PowderKeg") { fixtureType = FixtureType_PowderKeg; }
    else if (fixtureTypeStr == "Explosion") { fixtureType = FixtureType_Explosion; }
    else if (fixtureTypeStr == "EnemyAI") { fixtureType = FixtureType_EnemyAI; }
    else if (fixtureTypeStr == "EnemyAIMeleeSensor") { fixtureType = FixtureType_EnemyAIMeleeSensor; }
    else if (fixtureTypeStr == "EnemyAIDuckMeleeSensor") { fixtureType = FixtureType_EnemyAIDuckMeleeSensor; }
    else if (fixtureTypeStr == "EnemyAIRangedSensor") { fixtureType = FixtureType_EnemyAIRangedSensor; }
    else if (fixtureTypeStr == "EnemyAIDuckRangedSensor") { fixtureType = FixtureType_EnemyAIDuckRangedSensor; }
    else if (fixtureTypeStr == "DamageAura") { fixtureType = FixtureType_DamageAura; }
    else
    {
        assert(false && "Unknown body type");
    }

    return fixtureType;
}

//=============================================================================
// DamageType
//=============================================================================

DamageType StringToDamageTypeEnum(const std::string& str)
{
    static const std::map<std::string, DamageType> s_StringToDamageTypeEnumMap =
    {
        { "DamageType_None", DamageType_None },
        { "DamageType_MeleeAttack", DamageType_MeleeAttack },
        { "DamageType_Bullet", DamageType_Bullet },
        { "DamageType_Magic", DamageType_Magic },
        { "DamageType_Explosion", DamageType_Explosion },
        { "DamageType_FireSword", DamageType_FireSword },
        { "DamageType_LightningSword", DamageType_LightningSword },
        { "DamageType_FrostSword", DamageType_FrostSword }
    };

    auto findIt = s_StringToDamageTypeEnumMap.find(str);
    if (findIt == s_StringToDamageTypeEnumMap.end())
    {
        LOG_ERROR("Could not find DamageType: " + str);
        assert(false);
    }

    return findIt->second;
}

//=============================================================================
// b2BodyType
//=============================================================================

b2BodyType BodyTypeStringToEnum(std::string bodyTypeStr)
{
    b2BodyType bodyType = b2_staticBody;

    if (bodyTypeStr == "Static") { bodyType = b2_staticBody; }
    else if (bodyTypeStr == "Kinematic") { bodyType = b2_kinematicBody; }
    else if (bodyTypeStr == "Dynamic") { bodyType = b2_dynamicBody; }
    else
    {
        assert(false && "Unknown body type");
    }

    return bodyType;
}

//=============================================================================
// Direction
//=============================================================================

Direction StringToEnum_Direction(std::string dirStr)
{
    static const std::map<std::string, Direction> directionEnumToStringMap =
    {
        { "Direction_Up", Direction_Up },
        { "Direction_Down", Direction_Down },
        { "Direction_Left", Direction_Left },
        { "Direction_Right", Direction_Right },
    };

    auto findIt = directionEnumToStringMap.find(dirStr);
    if (findIt == directionEnumToStringMap.end())
    {
        LOG_ERROR("Could not find Direction: " + dirStr);
        assert(false);
    }

    return findIt->second;
}

std::string EnumToString_Direction(Direction dir)
{
    static std::map<Direction, std::string> stringToDirectionEnumMap =
    {
        // Actor enemies
        { Direction_Up, "Direction_Up" },
        { Direction_Down, "Direction_Down" },
        { Direction_Left, "Direction_Left" },
        { Direction_Right, "Direction_Right" },
    };

    auto findIt = stringToDirectionEnumMap.find(dir);
    if (findIt == stringToDirectionEnumMap.end())
    {
        LOG_ERROR("Could not find direction enum: " + ToStr((int)dir));
        assert(false && "Could not convert Direction enum to string");
    }

    return findIt->second;
}