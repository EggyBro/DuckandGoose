/*!*************************************************************************
****
\file PlayerController.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Player Controller
****************************************************************************
***/
#include "empch.h"
#include "PlayerController.h"

namespace EM
{

    /*!*************************************************************************
    Default constructor for Player Controller
    ****************************************************************************/
    PlayerController::PlayerController() : mState{ PlayerState::Idle }, mAttackCounter{ 0 }, mCooldownTimer{ 0.0f }, mChargedAttackTimer{ 0.0f }, mDashTimer{0.0f}, mBlockTimer{0.0f},
        mIsBlocking{ false }, mIsAttacking{ false }, mIsStunned{ false }, mIsIdle{ false }, mIsMoving{ false }, mIsDashing{ false }, mVel{ vec2D() } {};

    /*!*************************************************************************
    Returns a new copy of PlayerController Script
    ****************************************************************************/
	PlayerController* PlayerController::Clone() const
	{
		return new PlayerController(*this);
	}

    /*!*************************************************************************
    Start State of PlayerController Script
    ****************************************************************************/
	void PlayerController::Start()
	{
		mState = PlayerState::Idle;
	}

    /*!*************************************************************************
    Update Loop of Player Controller Script
    ****************************************************************************/
	void PlayerController::Update(float Frametime)
	{
        mCooldownTimer -= Frametime;
        mDashTimer -= Frametime;
        mBlockTimer -= Frametime;
        mVel.x = 0.0f;
        mVel.y = 0.0f;

        if ((p_Input->KeyHold(GLFW_KEY_W) || p_Input->KeyHold(GLFW_KEY_D)
            || p_Input->KeyHold(GLFW_KEY_S) || p_Input->KeyHold(GLFW_KEY_A)) && !mIsStunned)
        {   
            mCooldownTimer = 0.1f;
            if (p_Input->KeyHold(GLFW_KEY_W)) {
                mVel.y += 100.0f;
                mIsMoving = true;
                mIsAttacking = false;
                mIsIdle = false;
            }
            else if (p_Input->KeyHold(GLFW_KEY_S)) {
                mVel.y -= 100.f;
                mIsMoving = true;
                mIsAttacking = false;
                mIsIdle = false;
            }
            else if (p_Input->KeyHold(GLFW_KEY_D)) {
                mVel.x += 100.f;
                mIsMoving = true;
                mIsAttacking = false;
                mIsIdle = false;
                if (p_Input->isKeyPressed(GLFW_KEY_LEFT_SHIFT) && !mIsStunned && mDashTimer <= 0.0f)
                {
                    mVel.x += 2000.f;
                    mCooldownTimer = 0.5f;
                    mDashTimer = 5.0f;
                    mIsDashing = true;
                    mIsMoving = false;
                    mIsAttacking = false;
                    mIsIdle = false;
                }
            }
            else if (p_Input->KeyHold(GLFW_KEY_A)) {
                mVel.x -= 100.f;
                mIsMoving = true;
                mIsAttacking = false;
                mIsIdle = false;
                if (p_Input->isKeyPressed(GLFW_KEY_LEFT_SHIFT) && !mIsStunned && mDashTimer <= 0.0f)
                {
                    mVel.x -= 2000.f;
                    mCooldownTimer = 0.5f;
                    mDashTimer = 5.0f;
                    mIsDashing = true;
                    mIsMoving = false;
                    mIsAttacking = false;
                    mIsIdle = false;
                }
            }
        }

        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && !mIsStunned && mCooldownTimer <= 0.0f)
        {
            ++mAttackCounter;
            mCooldownTimer = 0.5f;
            mIsAttacking = true;
            mIsMoving = false;
            mIsIdle = false;
        }

        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_RIGHT) && !mIsStunned && mBlockTimer <= 0.0f)
        {
            mCooldownTimer = 0.5f;
            mBlockTimer = 5.0f;
            mIsBlocking = true;
            mIsMoving = false;
            mIsIdle = false;
        }

        if (mCooldownTimer <= 0.0f)
        {
            mIsIdle = true;
            mIsBlocking = false;
            mIsAttacking = false;
            mIsDashing = false;
        }

        UpdateState();
        UpdatePhysics(Frametime);
        Animate(mState);
	}

    /*!*************************************************************************
    End State for Player Controller
    ****************************************************************************/
    void PlayerController::End()
    {
        delete this;
    }

    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string PlayerController::GetScriptName()
    {
        return "PlayerController";
    }

    /*!*************************************************************************
    Function to update current player state
    ****************************************************************************/
    void PlayerController::UpdateState()
    {
        if (mIsBlocking)
        {
            mState = PlayerState::Block;
        }
        if (mIsAttacking)
        {
            mState = PlayerState::Attacking;
        }
        if (mIsStunned)
        {
            mState = PlayerState::Stunned;
        }
        if (mIsMoving)
        {
            mState = PlayerState::Moving;
        }
        if (mIsDashing)
        {
            mState = PlayerState::Dash;
        }
        if (mIsIdle)
        {
            mState = PlayerState::Idle;
        }
    }

    /*!*************************************************************************
    Update Physics for Player
    ****************************************************************************/
    void PlayerController::UpdatePhysics(float Frametime)
    {
        auto& pRigid = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetScriptEntityID());


        pRigid.SetVel(mPhys.friction(pRigid.GetVel(), Frametime));
        pRigid.SetVel(mPhys.accelent(pRigid.GetVel(), mVel, Frametime));
        vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
        pRigid.SetNextPos(nextPos);
    }

    /*!*************************************************************************
    Animate Player base on Texture set during player state
    ****************************************************************************/
    void PlayerController::Animate(PlayerState state)
    {
        switch (state)
        {
        case PlayerState::Idle:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Idle");
            break;
        case PlayerState::Moving:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Running");
            break;
        case PlayerState::Attacking:
            switch (mAttackCounter)
            {
            case 1:
                p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("CA1");
                break;
            case 2:
                p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("CA2");
                break;
            case 3:
                p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("CA3");
                break;
            case 4:
                p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("CA4");
                mAttackCounter = 0;
                break;
            }
            break;
        case PlayerState::Dash:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Dashing");
            break;
        case PlayerState::Block:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Blocking");
            break;
        }
    }
}