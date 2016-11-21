#include "HumanView.h"
#include "../GameApp/BaseGameApp.h"
#include "../GameApp/BaseGameLogic.h"
#include "../Events/EventMgr.h"
#include "../Events/Events.h"

const uint32 g_InvalidGameViewId = 0xFFFFFFFF;

HumanView::HumanView(SDL_Renderer* renderer)
{
    m_pProcessMgr = new ProcessMgr();

    m_ViewId = INVALID_GAME_VIEW_ID;

    RegisterAllDelegates();

    if (renderer)
    {
        m_pScene.reset(new ScreenElementScene(renderer));
        m_pCamera.reset(new CameraNode(Point(0, 0), 0, 0));
        m_pHUD.reset(new ScreenElementHUD());

        m_pScene->AddChild(INVALID_ACTOR_ID, m_pCamera);
        m_pScene->SetCamera(m_pCamera);

        m_pConsole = unique_ptr<Console>(new Console(g_pApp->GetWindowSize().x, g_pApp->GetWindowSize().y / 2,
            g_pApp->GetConsoleFont(), renderer, "console02.tga"));
    }
}

HumanView::~HumanView()
{
    RemoveAllDelegates();

    while (!m_ScreenElements.empty())
    {
        m_ScreenElements.pop_front();
    }

    SAFE_DELETE(m_pProcessMgr);
}

void HumanView::VOnRender(uint32 msDiff)
{
    //PROFILE_CPU("HumanView Render");

    m_CurrentTick = SDL_GetTicks();
    if (m_CurrentTick == m_LastDraw)
    {
        return;
    }

    SDL_Renderer* renderer = g_pApp->GetRenderer();

    if (m_RunFullSpeed || true)
    {
        //PROFILE_CPU(".");
        SDL_RenderClear(renderer);

        // Sort screen elements
        m_ScreenElements.sort(SortBy_SharedPtr_Content<IScreenElement>());

        for (shared_ptr<IScreenElement> screenElement : m_ScreenElements)
        {
            
            if (screenElement->VIsVisible())
            {
                screenElement->VOnRender(msDiff);
            }
        }

        g_pApp->GetGameLogic()->VRenderDiagnostics(renderer, m_pCamera);

        m_pConsole->OnRender(renderer);

        SDL_RenderPresent(renderer);
    }
}

void HumanView::VOnUpdate(uint32 msDiff)
{
    m_pProcessMgr->UpdateProcesses(msDiff);

    m_pConsole->OnUpdate(msDiff);

    for (shared_ptr<IScreenElement> element : m_ScreenElements)
    {
        element->VOnUpdate(msDiff);
    }
}

bool HumanView::VOnEvent(SDL_Event& evt)
{
    // First let console try to eat this event
    if (m_pConsole->OnEvent(evt))
    {
        //LOG("command eaten !");
        return true;
    }

    // Then screen layers in reverse order
    for (ScreenElementList::reverse_iterator i = m_ScreenElements.rbegin(); i != m_ScreenElements.rend(); ++i)
    {
        if ((*i)->VIsVisible())
        {
            if ((*i)->VOnEvent(evt))
            {
                return true;
            }
        }
    }

    switch (evt.type)
    {
        case SDL_KEYDOWN:
        {
            if (evt.key.repeat == 0)
            {
                return m_pKeyboardHandler->VOnKeyDown(evt.key.keysym.sym);
            }
        }
        case SDL_KEYUP:
        {
            if (evt.key.repeat == 0)
            {
                return m_pKeyboardHandler->VOnKeyUp(evt.key.keysym.sym);
            }
        }

        case SDL_MOUSEMOTION:
        {
            return m_pPointerHandler->VOnPointerMove(evt.motion);
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            return m_pPointerHandler->VOnPointerButtonDown(evt.button);
        }
        case SDL_MOUSEBUTTONUP:
        {
            return m_pPointerHandler->VOnPointerButtonUp(evt.button);
        }
        default:
            return false;
    }

    return false;
}

void HumanView::VOnLostDevice()
{

}

bool HumanView::LoadGame(TiXmlElement* pLevelData)
{
    return VLoadGameDelegate(pLevelData);
}

void HumanView::VPushElement(shared_ptr<IScreenElement> element)
{
    m_ScreenElements.push_front(element);
}

void HumanView::VRemoveElement(shared_ptr<IScreenElement> element)
{
    m_ScreenElements.remove(element);
}

void HumanView::VSetCameraOffset(int32 offsetX, int32 offsetY)
{
    if (m_pCamera)
    {
        m_pCamera->SetCameraOffset(offsetX, offsetY);
    }
    else
    {
        LOG_WARNING("Trying to set offset to nonexistant camera");
    }
}

void HumanView::RegisterAllDelegates()
{
    IEventMgr* pEventMgr = IEventMgr::Get();
    pEventMgr->VAddListener(MakeDelegate(this, &HumanView::NewHUDElementDelegate), EventData_New_HUD_Element::sk_EventType);
    pEventMgr->VAddListener(MakeDelegate(this, &HumanView::UpdateScoreDelegate), EventData_Update_Score::sk_EventType);
}

void HumanView::RemoveAllDelegates()
{
    IEventMgr* pEventMgr = IEventMgr::Get();
    pEventMgr->VRemoveListener(MakeDelegate(this, &HumanView::NewHUDElementDelegate), EventData_New_HUD_Element::sk_EventType);
    pEventMgr->VRemoveListener(MakeDelegate(this, &HumanView::UpdateScoreDelegate), EventData_Update_Score::sk_EventType);
}

//=====================================================================================================================
// Delegates
//=====================================================================================================================

void HumanView::NewHUDElementDelegate(IEventDataPtr pEventData)
{
    shared_ptr<EventData_New_HUD_Element> pCastEventData = static_pointer_cast<EventData_New_HUD_Element>(pEventData);
    if (m_pHUD)
    {
        m_pHUD->AddHUDElement(pCastEventData->GetHUDKey(), pCastEventData->GetHUDElement());
    }
    else
    {
        LOG_ERROR("HUD is unitialized");
    }
}

void HumanView::UpdateScoreDelegate(IEventDataPtr pEventData)
{
    shared_ptr<EventData_Update_Score> pCastEventData = static_pointer_cast<EventData_Update_Score>(pEventData);
    if (m_pHUD)
    {
        m_pHUD->UpdateScore(pCastEventData->GetNewScore());
        if (!pCastEventData->IsInitialScore())
        {
            if ((pCastEventData->GetOldScore() / 1000000) != (pCastEventData->GetNewScore() / 1000000))
            {
                // Add new life
            }
        }
    }
    else
    {
        LOG_ERROR("HUD is unitialized");
    }
}